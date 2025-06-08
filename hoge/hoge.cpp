#include <cstddef>
#include <memory>
#include <list>
#include <vector>
#include <queue>
#include <utility>
#include <numeric>

using usize = std::size_t;

template<class T_>
struct TwinVector final {
	std::vector<T_> buf;
	std::vector<usize> empty_idx;

	static auto make(const usize n) -> TwinVector {
		std::vector<T_> buf{};
		buf.reserve(n);
		std::vector<usize> empty_idx{};
		empty_idx.resize(n);
		std::ranges::iota(empty_idx, 0);
		return TwinVector {
			.buf = std::move(buf)
			, .empty_idx = std::move(empty_idx)
		};
	}

	auto add(T_&& x) -> usize {
		if(empty_idx.empty()) {
			throw std::runtime_error{"TwinVector: size over"};
		}

		const usize handle = empty_idx.back();
		empty_idx.pop_back();
		buf[handle] = std::move(x);
		return handle;
	}

	void remove(usize handle) {
		if(buf.size() <= handle) {
			throw std::runtime_error{"TwinVector: wrong handle"};
		}

		buf[handle] = {};
		empty_idx.push_back(handle);
	}

	template<class Self_>
	auto get(this Self_&& self, usize handle) -> decltype(std::forward_like<Self_>(std::declval<T_>())) {
		return std::forward_like<Self_>(self.buf[handle]);
	}
};

struct GameUnit {
	virtual auto get_z() const -> int = 0;
	virtual void draw() const = 0;
	virtual void update() = 0;
};

template<class T_>
using PrioGreaterQueue = std::priority_queue<T_, std::vector<T_>, std::greater<T_>>;

struct DrawTask final {
	const GameUnit * p;
	int loop_epoch;

	friend auto operator<(const DrawTask& l, const DrawTask& r) -> bool {
		return l.loop_epoch != r.loop_epoch ? l.loop_epoch < r.loop_epoch
			: l.p->get_z() < r.p->get_z()
		;
	}
};

struct NilUnit final : GameUnit {
	virtual auto get_z() const -> int override {
		return 0;
	}

	virtual void draw() const override {}
	virtual void update() override {}
};

struct Executor final {
	TwinVector<std::unique_ptr<GameUnit>> container;
	PrioGreaterQueue<DrawTask> draw_queue;
	int loop_epoch;

	static auto make() -> Executor {
		Executor ret{{}, {}, -1};
		ret.add(NilUnit{});
		return ret;
	}

	void add(GameUnit&& unit) {
		if(this->loop_epoch != -1) {
			throw "This implementation doesn't support runtime add.";
		}

		this->container.add(std::make_unique<GameUnit>(std::move(unit)));
		this->draw_queue.push(DrawTask{this->container.back().get(), 0});
	}

	void run_once() {
		for(const auto& up : container) {
			up->update();
		}

		DrawTask task = draw_queue.top();
		while(task.loop_epoch <= this->loop_epoch) {
			draw_queue.pop();
			task.p->draw();
			draw_queue.push(DrawTask{task.p, this->loop_epoch + 1});
			task = draw_queue.top();
		}
		this->loop_epoch++;
	}
};

void setup()

int main() {


	while(true) {

	}
}
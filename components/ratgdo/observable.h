#pragma once

namespace esphome {
namespace ratgdo {

    template<typename T>
    class observable {
    public:
        observable(const T& val): value(val) {}

        template<typename U> 
        observable& operator=(U value) {
            if (value != this->value) {
                this->value = value;
                this->notify();
            }
            return *this;
        }

        T const* operator&() const { return &this->value; }
        T* operator&() { return &this->value; }

        T const& operator*() const { return this->value; }
        T& operator*() { return this->value; }

        template<typename Observer>
        void subscribe(Observer&& observer) {
            this->observers.push_back(observer);
        }

        void notify() {
            for (auto& observer: observers) {
                observer(value);
            }
        }

        T value;
    private:
        std::vector<std::function<void(T)>> observers;
    };

} // namespace ratgdo
} // namespace esphome

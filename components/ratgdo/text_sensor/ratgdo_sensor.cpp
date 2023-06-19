#include "../ratgdo_state.h"
#include "esphome/core/log.h"
#include "ratgdo_text_sensor.h"
#include <ctime>

namespace esphome {
namespace ratgdo {

    static const char* const TAG = "ratgdo.text_sensor";
    char timeString[std::size("yyyy-mm-ddThh:mm:ssZ")];

    void RATGDOSensor::dump_config()
    {
        LOG_SENSOR("", "RATGDO Sensor", this);
        ESP_LOGCONFIG(TAG, "  Type: Auto Close time");
    }

    void RATGDOSensor::on_auto_close_time_change(time_t autoCloseTime)
    {
        std::strftime(std::data(timeString), std::size(timeString), "%FT%TZ", std::gmtime(&autoCloseTime));
        ESP_LOGV(TAG, "Auto close time: %s", timeString);
        this->publish_state(timeString);
    }

} // namespace ratgdo
} // namespace esphome

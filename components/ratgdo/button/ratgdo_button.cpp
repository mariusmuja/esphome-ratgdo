#include "ratgdo_button.h"
#include "../ratgdo_state.h"
#include "esphome/core/log.h"

namespace esphome {
namespace ratgdo {

    static const char* const TAG = "ratgdo.button";

    void RATGDOButton::dump_config()
    {
        LOG_BUTTON("", "RATGDO Button", this);
        if (this->button_type_ == ButtonType::RATGDO_SYNC) {
            ESP_LOGCONFIG(TAG, "  Type: Sync");
        } else if (this->button_type_ == ButtonType::RATGDO_QUERY) {
            ESP_LOGCONFIG(TAG, "  Type: Query");
        }
    }

    void RATGDOButton::press_action()
    {
        if (this->button_type_ == ButtonType::RATGDO_SYNC) {
            this->parent_->sync();
        } else if (this->button_type_ == ButtonType::RATGDO_QUERY) {
            this->parent_->query();
        }
    }

} // namespace ratgdo
} // namespace esphome

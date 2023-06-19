import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import text_sensor
from esphome.const import CONF_ID

from .. import RATGDO_CLIENT_SCHMEA, ratgdo_ns, register_ratgdo_child

DEPENDENCIES = ["ratgdo"]

RATGDOTextSensor = ratgdo_ns.class_("RATGDOTextSensor", text_sensor.TextSensor, cg.Component)
RATGDOTextSensorType = ratgdo_ns.enum("RATGDOTextSensorType")

CONF_TYPE = "type"
TYPES = {
    "auto_close_time": RATGDOTextSensorType.RATGDO_AUTO_CLOSE_TIME,
}


CONFIG_SCHEMA = (
    text_sensor.text_sensor_schema(RATGDOTextSensor)
    .extend(
        {
            cv.Required(CONF_TYPE): cv.enum(TYPES, lower=True),
        }
    )
    .extend(RATGDO_CLIENT_SCHMEA)
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await text_sensor.register_text_sensor(var, config)
    await cg.register_component(var, config)
    cg.add(var.set_ratgdo_sensor_type(config[CONF_TYPE]))
    await register_ratgdo_child(var, config)

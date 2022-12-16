# C Library for NB-IoT

![Tests](https://github.com/aungkhantmaw64/nbiot-driver/actions/workflows/workflow.yml/badge.svg)

## Architectural Diagram

```mermaid
classDiagram
    class ModemControllerTest{

    }

    class ModemController{
        +Create(SerialIO_t serial, int resetPin)
        +Destroy() void
        +RebootUE(void) int
        +HardReboot(void) int
        +IsReady(void) bool
    }

    class TimeService{
        <<interface>>
        + getMillis(void) uint32_t
    }

    class FakeTimeService{

    }

    class SerialIO{
        <<interface>>
        +SerialIO_Create(int number, uint32_t baudrate)
        +SerialIO_Destroy() void
        +SerialIO_Read() char
        +SerialIO_Write(char byte) void
        +SerialIO_ReadStringUntil(char *buffer, char end, uint32_t timeout_ms) void
    +SerialIO_Print(SerialIO_t serial, const char *text) void
    +SerialIO_IsAvailable(SerialIO_t serial) int
    }

    class BC95{

    }
    class SIM7020E{

    }
    ModemControllerTest --|> ModemController
    ModemControllerTest --|> FakeTimeService
    ModemController --* SerialIO: uses
    SerialIO <-- BC95: implements
    SerialIO <-- SIM7020E: implements
    ModemController --* TimeService: uses
    TimeService <-- FakeTimeService: implements

```
## Supported Devices
- [Quectel's BC95-G](https://www.mikroe.com/nb-iot-click)

![NBIOT-Click](./docs/images/nb-iot-click.jpg)

## References

- Unit testing - [Unity](https://github.com/ThrowTheSwitch/Unity)

- Mocking - [C Mock](https://github.com/ThrowTheSwitch/CMock)

- Build system - [Ceedling](https://github.com/ThrowTheSwitch/Ceedling)

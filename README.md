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
        +SetUEFunction(UEFunction_t mode) int
        +GetIMEI(void) String
        +GetIMSI(void) String
        +GetFirmwareVersion(void) String
        +PingIP(String IP) PingResponse_t
    }

    class TimeService{
        <<interface>>
        + getMillis(void) uint32_t
    }

    class FakeTimeService{

    }

    class SerialIO{
        <<interface>>
        +Create(int number, uint32_t baudrate)
        +Destroy() void
        +Read() char
        +Write(char byte) void
        +ReadStringUntil(char *buffer, char end, uint32_t timeout_ms) void
    +Print(const char *text) void
    +IsAvailable() int
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

## Running the tests
```
docker-compose up
```
## References

- Unit testing - [Unity](https://github.com/ThrowTheSwitch/Unity)

- Mocking - [C Mock](https://github.com/ThrowTheSwitch/CMock)

- Build system - [Ceedling](https://github.com/ThrowTheSwitch/Ceedling)

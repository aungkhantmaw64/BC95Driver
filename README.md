# Firmware Architecture & Test Cases

![Tests](https://github.com/aungkhantmaw64/nbiot-driver/actions/workflows/workflow.yml/badge.svg)

```mermaid
classDiagram
    class ModemController{
        +Create(SerialIO_t serial, int resetPin)
        +Destroy() void
        +RebootUE(void) void
        +HardReboot(void) void
        +IsReady(void) bool
    }

```
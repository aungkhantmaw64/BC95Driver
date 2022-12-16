# Firmware Architecture & Test Cases

![Tests](https://github.com/aungkhantmaw64/nbiot-driver/actions/workflows/workflow.yml/badge.svg)

```mermaid
classDiagram
    class Modem{
        +rebootUE(void) void
        +hardReboot(void) void
        +isReady(void) bool
    }

```
# ESPHome Configuration for CompactIO

This repository contains configuration files for the [ESPHome](https://esphome.io/) project, specifically tailored for the CompactIO device. ESPHome is a system to control ESP32 based devices via simple yet powerful configuration files written in YAML. The provided configuration files enable you to quickly set up and deploy firmware for CompactIO, allowing seamless integration with your smart home system.

## Purpose

The purpose of this project is to provide pre-configured ESPHome YAML files for the CompactIO device. These configurations are designed to simplify the process of setting up and managing CompactIO, enabling features such as binary inputs from wall switches, light control through relays, and integration with platforms like Home Assistant.

## Prerequisites

Before proceeding, ensure you have the following:
- A CompactIO device.
- A computer with Python 3 installed.
- ESPHome installed on your system. You can install it using pip:
    ```bash
    pip install esphome
    ```
- A USB cable to connect the CompactIO device to your computer.

## Instructions to Upload Firmware

Follow these steps to upload the firmware onto your CompactIO device:

1. **Clone the Repository**:
   Clone this repository to your local machine:
    ```bash
    git clone https://github.com/compactio/esphome-starter/
    cd esphome-starter
    ```

2. **Connect the CompactIO Device**:
   Use a USB cable to connect your CompactIO device to your computer.

3. **Modify the Configuration (Optional)**:
    1. **Change the device name**

        Open main.yaml file

        ```yaml
        substitutions:
        node_name: compactio
        ```

        Change `node_name` in the `main.yaml` file to a unique name for your device. This name will be used to identify the device on your network.

    2. **Switch from Ethernet to Wi-Fi**

        By default the configuration uses Ethernet. If you want to use Wi-Fi, you need to comment out the Ethernet configuration and uncomment the Wi-Fi configuration.

        Open main.yaml file.
        ```yaml
        <<: !include common.yaml
        <<: !include compactio_v1.3.yaml
        <<: !include ethernet.yaml
        #<<: !include wifi.yaml
        ```
        In the above code, comment out the Ethernet configuration and uncomment the Wi-Fi configuration.

        Open wifi.yaml and set Wi-Fi credentials:
        ```yaml
        wifi:
        networks:
            - ssid: "<ssid>"
              password: "<password>"
        ```

4. **Compile and Upload the Firmware**:
   Run the following command to compile and upload the firmware to the CompactIO device:
    ```bash
    esphome run main.yaml
    ```

5. **Monitor Logs**:
   After the upload is complete, ESPHome will automatically start monitoring the device logs. You can use this to verify that the device is functioning correctly.
   If you want to monitor the logs later, you can use the following command:
    ```bash
    esphome logs main.yaml
    ```

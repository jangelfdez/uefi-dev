# uefi-dev

This project provides an environment from scratch for UEFI (Unified Extensible Firmware Interface) development. It includes a set of tools and examples to help you get started with UEFI development.

## First steps

To configure this project and execute an example, follow these steps:

1. Install the necessary dependencies by running the following commands:
    ```
    sudo apt install build-essential

    # Cross-compiler to generate UEFI images
    sudo apt install gcc-mingw-w64

    # Emulator to test your code inside a virtual environment
    sudo apt install qemu-system-x86
    
    # Tools to extract the required OVMF UEFI image to run your code inside Qemu
    sudo apt install rpm2cpio cpio
    ```

2. Clone the `uefi-dev` repository by running the following command:
    ```
    git clone https://github.com/jangelfdez/uefi-dev.git
    ```

3. Download the OVMF (Open Virtual Machine Firmware) UEFI image by running the following command. It uses one of the builds of the tianocore project to avoid compiling it from scratch:
    ```
    cd uefi-dev && mkdir OVMF-uefi-image && cd OVMF-uefi-image

    wget "https://www.kraxel.org/repos/jenkins/edk2/edk2.git-ovmf-x64-0-20220719.209.gf0064ac3af.EOL.no.nore.updates.noarch.rpm"

    rpm2cpio edk2.git-ovmf-x64-0-20220719.209.gf0064ac3af.EOL.no.nore.updates.noarch.rpm | cpio -idmv --no-absolute-filenames
    
    cp ./usr/share/edk2.git/ovmf-x64/OVMF-pure-efi.fd .
    
    rm *.rpm
    rm -rf ./usr/* && rmdir ./usr   

    cd ..
    ```

4. Build the project by running the following command:
    ```
    make all
    ```

5. Execute the default Hello World example by running the following command:
    ```
    make run-example 
    ```

6. Test other examples configuring the specific variable to launch them:
    ```
    make run-example EXAMPLE=build/uefi-tele-sketch.efi
    ```

Now you are ready to explore and develop UEFI applications using this project.

## Debugging your code with GDB

To debug your UEFI code using GDB, follow these steps:

1. Install GDB by running the following command:
    ```
    sudo apt install gdb
    ```

2. Build your UEFI project with debug symbols enabled. By default your Makefile include the `-g` flag when compiling. If you want to configure your own script, remember to add it yourself:
    ```
    CFLAGS += -g
    ```

3. Once your UEFI project is built with debug symbols, you can start debugging with GDB. Run the following command, it would configure QEMU to wait for gdb:
    ```
    make debug-example EXAMPLE=build/uefi-tele-sketch.efi
    ```

4. Open a new terminal and start the debugger. In the GDB prompt load the debugging information of your program and connect to the remote session started by QEMU:
    ```
    file build/uefi-tele-sketch.efi
    target remote localhost:1234
    ```

5. Configure a breakpoint in your main function and start the execution of your application:
    ```
    break efi_main
    continue
    ``` 

In the GDB prompt, you can set breakpoints, inspect variables, and step through your code. Here are some useful commands:
    - `break <line_number>`: Set a breakpoint at a specific line number.
    - `run`: Start executing the UEFI application.
    - `next`: Step to the next line of code.
    - `print <variable_name>`: Print the value of a specific variable.
    - `continue`: Continue execution until the next breakpoint or the program exits.

## Installing gdbgui

If you prefer a graphical interface for GDB, you can install `gdbgui` to simplify your debugging experience. Follow these steps:

1. Install Python and pip by running the following command:
    ```
    sudo apt install python3 python3-pip python3-venv
    ```

2. Create a new virtual environment and install the `gdbgui` using pip:
    ```
    python3 -m venv gdbdebug
    source gdbdebug/bin/activate
    pip3 install gdbgui
    ```

3. Once `gdbgui` is installed, you can start it by running the following command:
    ```
    gdbgui 
    ```

4. This will open a web browser with the `gdbgui` interface, where you can set breakpoints, inspect variables, and step through your code using a user-friendly graphical interface. Review steps 4 - 5 of the previous section to finish your configuration.

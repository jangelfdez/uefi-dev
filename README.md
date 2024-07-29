# uefi-dev

This project provides an environment from scratch for UEFI (Unified Extensible Firmware Interface) development. It includes a set of tools and examples to help you get started with UEFI development.

To configure this project and execute an example, follow these steps:

1. Install the necessary dependencies by running the following commands:
    ```
    sudo apt install build-essential
    sudo apt install gdb

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



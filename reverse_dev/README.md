# String Reverse Driver

The `reverse` is a device driver which allows you to write string and read it reversed.

## Warning

This software is dangerous. It can damage your whole system. We don't take responsibility for damaging your system because of using this software.
We recommend you run this software in a virtual machine for security reasons.

## Setting up the driver

To set the driver up, at first, you must compile it by executing the following command:
1. `cd dev`
2. `make`

After compilation, you must add the `reverse` module to your kernel. You can do that by executing:
1. `cd dev`
2. `sudo insmod reverse.ko`

Now your driver is set up and it is located in `/dev/reverse`

## Example

A usage example is located in `dev_usage_example` directory. To run the example, execute the following commands:
1. `cd dev_usage_example`
2. `gcc -o reverse_string main.c`
3. `sudo ./reverse_string`

On success, it must print out the following:

"
Wrote 5
Read 3
GOT: oll
Read 2
GOT: eH
"

# Server/client example using <sys/socket.h>
At the source folder you would find an example of a simple TCP server/client example, which only accepts one client, and a Multiclient TCP server/client example using the library <sys/socket.h>

## Summary

- [Getting Started](#getting-started-)
- [Pre-installation](#pre-installation-)
- [Installation](#installation-)
- [Deployment](#deployment-)
- [How it works](#how-it-works-) 
- [Build with](#build-with-)
- [License](#license-)
- [Acknowledgments](#acknowledgments-)

## Getting started 🚀

Download the source's folder on your computer.

## Pre-installation 📋

You need make packet to execute the files.

To install it:
```
sudo apt-get update
```
```
sudo apt-get install make
```
[Return to summary](#summary)

## Installation 🔧

Open your cmd, go to the directory where you have downloaded the files typing this:

```
cd Documents/Projects/source/Simple\ TCP for example
```
Now you have to compile them, typing:
```
make server
```
And:
```
make client
```
Or if you prefer you can type:
```
make all
```
These commands works for both projects.

[Return to summary](#summary)

## Deployment 📦

Then open some terminals and go to the directory where you have the files compiled.

It's very important to run the server before de client. At the first terminal run the server:
```
./server 8080
```
On the second the client:
```
./client 127.0.0.1 8080
```
When you do this you recieve a message on the server and on the client side saying that it was successfully or not in case of error.
Once connected you can send messages to the host until you type "Exit" to get disconnected.

As you can see the format is ./server port_number and ./client hostname port_number so you can try whatever you want.

**NOTE**: with Simple TCP example the maximum number of terminals are two, however for Multiclient's example you can execute whatever you want.

[Return to summary](#summary)

## How it works 🔨


[Return to summary](#summary)

## Build with 🛠️

* [VS Code](https://code.visualstudio.com/) - Code editor used
* [Creative Commons](https://creativecommons.org/) - Used to choose the license

[Return to summary](#summary)

## License 📄

This project is licensed under the [CC0 1.0 Universal](LICENSE.md)
Creative Commons License - see the [LICENSE.md](LICENSE.md) file for
details

[Return to summary](#summary)

## Acknowledgments 📢
* https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
* https://www.binarytides.com/server-client-example-c-sockets-linux/
* https://pubs.opengroup.org/onlinepubs/009696899/basedefs/sys/socket.h.html

[Return to summary](#summary)





# PenVeno: A Beginner-Friendly Penetration Testing Tool

PenVeno is a user-friendly penetration testing tool specifically designed for cybersecurity beginners. It offers essential functions such as operating system detection, port scanning, DNS mapping, and the creation of custom payloads. Developed in C++ for high performance and utilizing GTK+ for an accessible graphical user interface, PenVeno is perfect for students and early-career professionals interested in ethical hacking and network security.

Features:

+ OS Detection: Identify the operating system of a target device via IP address.

+ Port Scanning: Scan specific ports or a range of ports on a target device.

+ DNS Mapping: Map domain names to IP addresses for network analysis.

+ Payload Creation: Generate custom payloads for multiple operating systems (Windows, Linux, Mac, Android, iOS), with options for encryption and encoding.

+ Custom Wordlist: Create custom wordlists for password cracking.

# Installation
```
git clone https://github.com/ShanawazAlam007/PenVeno.git

cd PenVeno
```
# Install Dependencies:

Install GTK+ on Ubuntu or Linux:
```
sudo apt-get update
```
```
sudo apt-get install libgtkmm-3.0-dev
```

Install Nmap for scanning
```
sudo apt-get install nmap
```

Install msfvenom (part of Metasploit Framework)
```
sudo apt-get install metasploit-framework
```

Install crunch tool
```
sudo apt install crunch
```
# Compile the Program

```
g++ -o PenVeno PenVeno.c++ `pkg-config gtkmm-3.0 --cflags --libs`  
```
# Requirements

- Operating System: Linux
- Memory: Minimum 1 GB RAM
- Storage: Minimum 100 MB disk space
- Dependencies: GTK+, nmap, dnsmap, msfvenom , crunch

# Usage

PenVeno provides a graphical interface where users can select various penetration testing functionalities:

- OS Detection: Enter a target IP and detect the OS type and version.
- Port Scanning: Choose between single port or range scan modes for target IPs.
- DNS Mapping: Enter a domain name or IP to retrieve DNS mapping data.
- Payload Creation: Create custom payloads for different operating systems with selectable encryption options.


- Custom Wordlist: Generate custom wordlists for password cracking using the Crunch tool. Specify character sets, minimum and maximum word lengths, and other parameters to create tailored wordlists for your needs.

# ScreenShots

- OS Detection: Interface showing IP entry and result output.
  ![image](https://github.com/user-attachments/assets/c2ebffb0-fe2f-45ca-a079-50057f7db489)

- Port Scanning: Fields for entering IP, port, or port range.
  ![image](https://github.com/user-attachments/assets/1c9bea4e-963d-4160-87bd-11a8046c9b55)
  - Scanning a specific port:
     ![image](https://github.com/user-attachments/assets/bb49f3c9-0fa0-487c-9d91-cc5701d2a281)
  - Scanning a range of port:
     ![image](https://github.com/user-attachments/assets/dee91ae2-f51e-4868-bf68-11cd857b7c5b)
  - Shows the open port:
    ![image](https://github.com/user-attachments/assets/a87f27ba-ecb9-47f6-9f4e-1be01ea10530)
- Payload Creation: Interface for setting target OS, encryption, and custom payload name.
  ![image](https://github.com/user-attachments/assets/f84a14d7-1d10-42c5-affd-f55119bbf8ba)
  - Entering Detail for iterative encryption:
    ![image](https://github.com/user-attachments/assets/126731cb-f4d8-448f-a06f-8bd60264c25c)
  - Payload successfully created:
    ![image](https://github.com/user-attachments/assets/8c1eedcd-aaa3-4da3-bc66-2c556324d1db)

- Crunch Tool: Interface for generating custom wordlists. Users can specify character sets, minimum and maximum word lengths, and other parameters to create tailored wordlists for password cracking.
    - Selecting the Custom Wordlist option
      
       ![image](https://github.com/user-attachments/assets/da3fdc76-d659-43e2-900c-c8657428f752)
    - Creating Custom Wordlist
      
      ![image](https://github.com/user-attachments/assets/ddbfbea4-5bd0-4ed7-8d11-4a1888747316)

      - Output file:
        ![image](https://github.com/user-attachments/assets/ad37a405-c96b-428a-b08e-ca5553d704d3)



![Crunch](https://github.com/user-attachments/assets/b9a47a5f-4578-4d61-91ab-8479bea1cfb3)


# Contributing
 We welcome contributions to enhance PenVeno! Please follow these steps:

+ Fork the repository.
+ Create a new branch (git checkout -b feature/YourFeature).
+ Commit your changes (git commit -m "Add new feature").
+ Push to the branch (git push origin feature/YourFeature).
+ Open a pull request.

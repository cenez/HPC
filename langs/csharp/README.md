----

# This folder include a miscellaneous of examples and resources, target to **MPI** and **MONO** on Linux or Windows.
### Enviromment MPI and MONO on Linux:
1. Download the [mono_mpi_environment.tar.gz](https://drive.google.com/file/d/1juuCPMtXjgo2edPJn9GzRNpVGQQRMaVW/view?usp=sharing);
     - 1.1 Dependencies: You need install: libxml2-dev and git
     - 1.1.1 Ex: Ubuntu or Debian: 
     *      sudo apt update
     *      sudo apt install git libxml2-dev -y
2. Copy file to opt folder:
     *      sudo cp ~/DownloadFolder/mono_mpi_environment.tar.gz /opt/
     *      cd /opt/
     * Optional (without sudo) - change permission on /opt:
     *      sudo chown your_user:your_group /opt
3. "Unzip" the file:
     *      sudo tar -xzf mono_mpi_environment.tar.gz
5. Open the folder to install:
     *      cd mono_mpi_environment/
     *      ./sudo_install.sh # When used sudo permission
     *      ./root_install.sh # When used root permission
     - 5.1 read the enviromment variables of mono and mpi:
     *      source to_end.bashrc
     - 5.2 or **(close the terminal and open again)**
7. **mkdir /opt/workspace ; cd /opt/workspace**
8. **git clone https://github.com/cenez/HPC**
9. **cd langs/csharp/AulaMPI2/**
10. **./compile.sh**
11. To Run (4 process):
     - 9.1 **cd bin/**
     - 9.2 **mpirun -np 4 mono AulaMPI2.exe**
     - 9.3 **cd ../**
12. To Run Using Script (4 process):
     - **./compile_run.sh 4**
     - **OR just run, if you already compile:**
     - **./run.sh 4**

13. **The print is anything like:**
     * allToal: node 0 -> 0:0 0:1 0:2 0:3
     * allToal: node 1 -> 1:0 1:1 1:2 1:3
     * allToal: node 2 -> 2:0 2:1 2:2 2:3
     * allToal: node 3 -> 3:0 3:1 3:2 3:3

----

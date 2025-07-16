----

# This folder include a miscellaneous of examples and resources, target to run **MPI** and **MONO** on Linux.
### Enviromment MPI and MONO on Linux:
1. Download the [mono_mpi_environment.tar.gz](https://drive.google.com/file/d/1juuCPMtXjgo2edPJn9GzRNpVGQQRMaVW/view?usp=sharing);
     - 1.1 Dependencies: You need install: libxml2-dev and git
     - 1.1.1 Ex: Ubuntu or Debian: 
     *      sudo apt update
     *      sudo apt install git libxml2-dev -y
2. Copy the downloaded file ([mono_mpi_environment.tar.gz](https://drive.google.com/file/d/1juuCPMtXjgo2edPJn9GzRNpVGQQRMaVW/view?usp=sharing)) to /opt folder:
     *      sudo cp mono_mpi_environment.tar.gz /opt/
     *      cd /opt/
     * Optional (without sudo) - change permission on /opt:
     *      sudo chown your_user:your_group /opt
3. "Unzip" the file:
     *      sudo tar -xzf mono_mpi_environment.tar.gz
4. Open the folder to install:
     *      cd mono_mpi_environment/
     *      ./sudo_install.sh # When used sudo permission
     *      ./root_install.sh # When used root permission
     - 4.1 Read the enviromment variables of mono and mpi:
     *      source to_end.bashrc
     - 4.2 **Or close the terminal and open again**
     - 4.3 Test your enviromment:
     *      mpiexec -n 4 /bin/hostname
5. Create the workspace:
     *      mkdir /opt/workspace
     *      cd /opt/workspace
6. Clone the git HPC Projects:
     *      git clone https://github.com/cenez/HPC
     *      cd HPC/langs/csharp/AulaMPI2/
7. Compile the sources:
     *      ./compile.sh
8. To Run (4 process):
     *      cd bin/
     *      mpirun -np 4 mono AulaMPI2.exe
     *      cd ../
9. To Run Using Script (4 process):
     *      ./compile_run.sh 4
     - **OR just run, if you already compile:**
     *      ./run.sh 4

10. **The print is anything like:**
     * allToal: node 0 -> 0:0 0:1 0:2 0:3
     * allToal: node 1 -> 1:0 1:1 1:2 1:3
     * allToal: node 2 -> 2:0 2:1 2:2 2:3
     * allToal: node 3 -> 3:0 3:1 3:2 3:3

----

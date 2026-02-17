# RobotCar - 

### JavaFX GUI

### Run with Maven

1. Make sure **Java 17+** and **Maven** are installed on your system.  (Maven installation guide below)
2. Open a terminal/command prompt in the project folder. 
3. Change pom.xml to be specific to your OS, the submitted version is already preconfigured for windows.
    - to change it simply go to the pom.xml file
    - click ctrl+f, search win, and replace the win in the 3 * <classifier>win</classifier> with:
        - linux (if on linux)
        - mac-aarch64 (if on M-chip mac)
        - mac (if on intel mac)
4. Open terminal in the projects root folder:
mvn clean javafx:run

This should install our dependencies and run the Javafx GUI

---

### Maven installation guide:

If using Mac/Linux its easiest to do so using a package manager like Homebrew (https://brew.sh/)
Then in your terminal: brew install maven

If on Windows you can download maven here: https://maven.apache.org/download.cgi
Extract it somewhere, e.g., C:\Program Files\Apache\Maven.
Add Maven bin folder to your system PATH: 
    - press windows key + S
    - type in "edit the system environment variables" and open it
    - click on the environment variables button
    - under system variables (the bottom window), go to Path, click on it and click edit
    - click new, and add the path to your maven\bin folder e.g. C:\Program Files\Apache\Maven\apache-maven-3.9.11\bin
    - save it
Now open a terminal and type in:
mvn -v 

If its installed you should get information with the path to where it is stored
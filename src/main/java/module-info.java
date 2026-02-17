module com.project1 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.net.http;
    requires java.desktop;

    opens com.project1.view to javafx.fxml;
    exports com.project1;
}

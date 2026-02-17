package com.project1;
// This basically informs the compiler to put it in com/project1 (you can verify this by looking in the target folder)
// we need to compile it with maven since its a maven project, the IDE then knows to put the GUI.fxml in the same 
// folder as these classes

// This is our Javafx GUI (Not to be confused with the SwingGui in in the same folder)

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.io.IOException;

import com.project1.view.DashboardView;

// extends means that our App inherits all the methods from the JavaFx premade Application class
public class App extends Application {

    private static Scene scene;
    private DashboardView controller;

    
    // IOException is a java object representing input/output error, so for example if we cant load our GUI.fxml
    // then the fxmlloader.load() will throw an IOException which is passed to its Parent (so our start() method)
    // but then our parent passes it to their parent (the launch() method) which handles and prints out what the issue is
    // FXMLLoader.load() → start() → JavaFX runtime (via launch()) → prints error
    
    // override just means that we replace whatever the default start() method is in the Application class with the code below
    @Override
    public void start(Stage stage) throws IOException { 
        // This if if we want to start our window without the default OS close, expand, minimize buttons, but we'd need to create our own ones
        // primaryStage.initStyle(StageStyle.UNDECORATED);

        // So we load our layout of our GUI (kind of like HTML in web dev)
        FXMLLoader fxmlLoader = new FXMLLoader(App.class.getResource("GUI.fxml"));

        // We set our layout to be 1200 * 600 pixels
        scene = new Scene(fxmlLoader.load(), 1500, 600);

        // We load the style sheet for it (just like css in web dev)
        scene.getStylesheets().add(getClass().getResource("style.css").toExternalForm());

        // A stage is like a window frame, a scene is like the glass inside, our application only has one scene
        stage.setScene(scene);

        // We create the controller so that we can read key inputs
        controller = fxmlLoader.getController();
        controller.setupInputHandlers(scene);

        // // This is just so that when we use the arrow keys it doesnt move focus accross the UI
        // scene.getRoot().setFocusTraversable(true);
        // scene.getRoot().requestFocus(); 

        // When launched it should be centered on the screen
        stage.centerOnScreen();
        stage.show();
    }

    // 
    @Override
    public void stop() throws Exception {
        if (controller != null) {
            controller.shutdown();
        }
        super.stop();
    }
    
    public static void main(String[] args) {
        // launch() comes from the JavaFx Application class, it basically calls the start() method above
        // it passes in a default stage as a parameter into the start() method
        launch();
    }

}
package com.project1.view;

import com.project1.model.RobotModel;
import javafx.animation.AnimationTimer;
import javafx.geometry.Point2D;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

public class MapView {

    private final Canvas canvas;
    private final GraphicsContext gc;
    private final RobotModel model;

    private final double[] arrowXPoints = {6, -6, -6};
    private final double[] arrowYPoints = {0, -4, 4};
    private final double centreX;
    private final double centreY;

    public MapView(Canvas canvas, RobotModel model) {
        this.canvas = canvas;
        this.model = model;
        this.gc = canvas.getGraphicsContext2D();
        this.centreX = canvas.getWidth() / 2.0;
        this.centreY = canvas.getHeight() / 2.0;
    }

    public void startRendering() {
        new AnimationTimer() {
            @Override
            public void handle(long now) {
                render();
            }
        }.start();
    }

    private void render() {
        // Clear screen
        gc.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());

        // Get the position from the model instead of caculating it here
        double currentX = model.getX();
        double currentY = model.getY();
        double currentAngle = model.getAngle();

        gc.save();

        // This makes it so our new centre is at our last location
        double offsetX = centreX - currentX;
        double offsetY = centreY - currentY;
        gc.translate(offsetX, offsetY);

        // Redraw all the points so far (this way theyre offset from the new centre)
        drawPath();

        // Just gets back our previous values before the offset so we can draw the arrow in the centre
        gc.restore();
        
        drawArrow(currentAngle);
    }

    private void drawPath() {
        // synchronized means that this will wait until the position has stopped being updated
        // this is to prevent executing this while the position is being overwritten, as it could cause the wrong position to be rendered
        synchronized (model.getPositionHistory()) {
            if (model.getPositionHistory().isEmpty()) return;

            gc.setStroke(Color.valueOf("#4F1C51"));
            gc.setLineWidth(2);

            // We draw a line connecting each point in our position history
            for (int i = 1; i < model.getPositionHistory().size(); i++) {
                Point2D p1 = model.getPositionHistory().get(i - 1);
                Point2D p2 = model.getPositionHistory().get(i);
                gc.strokeLine(p1.getX(), p1.getY(), p2.getX(), p2.getY());
            }
        }
    }

    private void drawArrow(double angleRadians) {
        gc.save();
        gc.translate(centreX, centreY);
        
        // JavaFX rotation is clockwise (degrees), Math is counter-clockwise (radians)
        gc.rotate(-Math.toDegrees(angleRadians));

        gc.setFill(Color.valueOf("#210F37"));
        gc.fillPolygon(arrowXPoints, arrowYPoints, 3);
        gc.restore();
    }
    
}
package acamo;

import java.lang.Thread.State;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.stream.IntStream;

import de.saring.leafletmap.LatLong;
import de.saring.leafletmap.LeafletMapView;
import de.saring.leafletmap.MapConfig;
import de.saring.leafletmap.MapLayer;
import de.saring.leafletmap.Marker;
import de.saring.leafletmap.ScaleControlConfig;
import de.saring.leafletmap.ZoomControlConfig;
import de.saring.leafletmap.events.MapClickEventListener;
import javafx.application.Application;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.concurrent.Worker;
import javafx.event.EventHandler;
import javafx.geometry.Insets;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.control.TextField;
import javafx.scene.control.cell.PropertyValueFactory;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.text.Font;
import javafx.stage.Stage;
import jsonstream.PlaneDataServer;
import messer.BasicAircraft;
import messer.Messer;
import observer.Observable;
import observer.Observer;
import senser.Senser;

public class Acamo extends Application implements Observer<BasicAircraft> {

    private static double latitude = 48.7433425;
    private static double longitude = 9.3201122;
    private boolean haveConnection = true;
    private ActiveAircrafts activeAircrafts;
    private static int dist = 50;

    private TableView<BasicAircraft> table = new TableView<BasicAircraft>();
    private ObservableList<BasicAircraft> aircraftList = FXCollections.observableArrayList();
    ArrayList<Label> valueLabel = new ArrayList<Label>();
    private int str = -1;

    private HashMap<String, Marker> aircraftHashMap = new HashMap<String, Marker>();
    private CompletableFuture<Worker.State> loadingState;
    private LeafletMapView map = new LeafletMapView();
    private TextField inputLong;
    private TextField inputLat;
    private Marker homeMarker;
    private PlaneDataServer server;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage arg0) throws Exception {
        String urlString = "https://opensky-network.org/api/states/all";

        if (haveConnection){
            server = new PlaneDataServer(urlString, latitude, longitude, 50);
        }
        else{
            server = new PlaneDataServer(latitude, longitude, 50);
        }
        
        Senser senser = new Senser(server);
        new Thread(server).start();
        new Thread(senser).start();

        Messer messer = new Messer();
        senser.addObserver(messer);
        new Thread(messer).start();

        activeAircrafts = new ActiveAircrafts();
        messer.addObserver(activeAircrafts);
        messer.addObserver(this);

        javafx(arg0);
    }

    private void javafx(Stage arg0) {

        // Map
        Label mapTitle = createTitle("Map", new Insets(0, 0, 20, 0), 24);
        List<MapLayer> config = new ArrayList<>();
        config.add(MapLayer.OPENSTREETMAP);
        config.add(MapLayer.OPENSTREETMAP);
        loadingState = map.displayMap(new MapConfig(config, new ZoomControlConfig(),
                new ScaleControlConfig(), new LatLong(latitude, longitude)));

        loadingState.whenComplete((State, Throwable) -> {
            map.onMapClick(new MapClickEventListener() {

                @Override
                public void onMapClick(LatLong coord) {
                    inputLat.setText(String.valueOf(coord.getLatitude()));
                    inputLong.setText(String.valueOf(coord.getLongitude()));
                    switchLocation(coord.getLatitude(), coord.getLongitude(), dist);
                }

            });

            homeMarker = new Marker(new LatLong(latitude, longitude), "Home", "Home", 1);
            map.addCustomMarker("Home", "icons/basestationlarge.png");
            map.addMarker(homeMarker);

            for (int i = 0; i <= 24; i++) {
                String n = String.format("%02d", i);
                map.addCustomMarker("plane" + n, "icons/plane" + n + ".png");
            }
        });

        for (BasicAircraft bac : activeAircrafts.values()) {
            int direction = (int) bac.getTrak();
            LatLong coord = new LatLong(bac.getCoordinate().getLatitude(), bac.getCoordinate().getLongitude());
            String icao = bac.getIcao();
            String icon = "plane" + String.format("%02d", direction / 15);
            if (aircraftHashMap.containsKey(icao)) {
                Marker plane = aircraftHashMap.get(icao);
                plane.move(coord);
                plane.changeIcon(icon);
            } else {
                loadingState.whenComplete((state, throwable) -> {
                    Marker plane = new Marker(coord, icao, icon, 0);
                    map.addMarker(plane);
                    aircraftHashMap.put(icao, plane);
                });
            }
        }
        

        map.setMaxWidth(500);
        map.setMaxHeight(400);

        Label label = createTitle("Active Aircrafts", new Insets(0, 0, 20, 0), 24);
        ArrayList<String> tableAttributes = BasicAircraft.getAttributesNames();
        tableAttributes.forEach(attribute -> {
            TableColumn<BasicAircraft, String> tableHeader = new TableColumn<BasicAircraft, String>(attribute);
            tableHeader.setCellValueFactory(new PropertyValueFactory<BasicAircraft, String>(attribute));
            table.getColumns().add(tableHeader);
        });
        table.setItems(aircraftList);
        table.setEditable(false);

        GridPane selectedAircraftPane = new GridPane();
        selectedAircraftPane.setHgap(20);
        Label selectedTitle = createTitle("Selected Aircraft", new Insets(0, 0, 20, 0), 24);

        String[] ld = { "icao:", "operator:", "posTime:", "coordinates:", "speed:", "trak:" };
        ArrayList<Label> nl = new ArrayList<Label>();
        IntStream.range(0, ld.length).forEach(i -> {
            nl.add(new Label(ld[i]));
            selectedAircraftPane.add(nl.get(i), 0, i);

            valueLabel.add(new Label(""));
            selectedAircraftPane.add(valueLabel.get(i), 1, i);
        });

        // controls for switching position
        Label latLabel = createTitle("Latitude:", new Insets(5, 0, 5, 0), 14);
        inputLat = new TextField();
        inputLat.setText(String.valueOf(latitude));

        Label lngLabel = createTitle("Longitude:", new Insets(5, 0, 5, 0), 14);
        inputLong = new TextField();
        inputLong.setText(String.valueOf(longitude));

        Button submit = new Button("Submit");
        submit.setOnAction(e -> {
            switchLocation(Double.parseDouble(inputLat.getText()), Double.parseDouble(inputLong.getText()), dist);
        });

        HBox ct = new HBox();
        VBox mB = new VBox();
        VBox tb = new VBox();
        VBox sb = new VBox();

        mB.setPadding(new Insets(0, 10, 0, 0));
        mB.getChildren().addAll(mapTitle, map, latLabel, inputLat, lngLabel, inputLong, submit);

        tb.setPadding(new Insets(0, 10, 0, 0));
        tb.getChildren().addAll(label, table);

        sb.setPadding(new Insets(0, 0, 0, 10));
        sb.getChildren().addAll(selectedTitle, selectedAircraftPane);

        ct.setPadding(new Insets(20, 20, 20, 20));
        ct.getChildren().addAll(mB, tb, sb);

        // export event Handler
        rowSelectedEvent();

        Scene scene = new Scene(ct, 1310, 600);
        arg0.setOnCloseRequest(e -> System.exit(0));
        arg0.setScene(scene);
        arg0.setTitle("Acamo");
        arg0.show();
    }

    public void rowSelectedEvent() {
        table.setOnMouseClicked(new EventHandler<MouseEvent>() {

            public void handle(MouseEvent e) {
                try {

                    str = table.getSelectionModel().getSelectedIndex();

                    BasicAircraft bac = table.getSelectionModel().getSelectedItem();
                    ArrayList<Object> values = BasicAircraft.getAttributesValues(bac); // ERROR
                    for (int i = 0; i < values.size(); i++) {
                        valueLabel.get(i).setText(values.get(i).toString());
                    }
                } catch (NullPointerException ex) {

                }
            }
        });
    }


    private Label createTitle(String string, Insets insets, int i) {
        Label label = new Label(string);
        label.setPadding(insets);
        label.setFont(new Font(i));

        return label;
    }

    @Override
    public void update(Observable<BasicAircraft> observable, BasicAircraft newValue) {
        Platform.runLater(new Runnable() {
            @Override
            public void run() {
                aircraftList.clear();
                aircraftList.addAll(activeAircrafts.values());
                try {
                    if (str >= 0) {
                        table.getSelectionModel().select(str);
                        BasicAircraft bac = table.getSelectionModel().getSelectedItem();
                        ArrayList<Object> values = BasicAircraft.getAttributesValues(bac);
                        for (int i = 0; i < values.size(); i++) {
                            valueLabel.get(i).setText(values.get(i).toString());
                        }
                    }
                } catch (NullPointerException e) {
                }

                for (BasicAircraft bac : activeAircrafts.values()) {
                    int direction = (int) bac.getTrak();
                    LatLong coord = new LatLong(bac.getCoordinate().getLatitude(), bac.getCoordinate().getLongitude());
                    String icao = bac.getIcao();
                    String icon = "plane" + String.format("%02d", direction / 15);
                    if (aircraftHashMap.containsKey(icao)) {
                        Marker plane = aircraftHashMap.get(icao);
                        plane.move(coord);
                        plane.changeIcon(icon);
                    } else {
                        loadingState.whenComplete((state, throwable) -> {
                            Marker plane = new Marker(coord, icao, icon, 0);
                            map.addMarker(plane);
                            aircraftHashMap.put(icao, plane);
                        });
                    }
                }
            }
        });
    }

    public void switchLocation(double lat, double lng, int dist) {
        map.panTo(new LatLong(lat, lng));
        homeMarker.move(new LatLong(lat, lng));
        activeAircrafts.clear();
        aircraftList.clear();
        for (Marker mark : aircraftHashMap.values()) {
            map.removeMarker(mark);
        }
        aircraftHashMap.clear();
        server.resetLocation(lat, lng, dist);
    }

}

package messer;

import java.util.Date;

import org.json.JSONArray;

import senser.AircraftSentence;

public class BasicAircraftFactory {
    public BasicAircraft createAircraft(AircraftSentence as) {
        JSONArray aircraftData = as.getData();
        Coordinate coordinate = new Coordinate(aircraftData.getDouble(6), aircraftData.getDouble(5));
        Date d = new Date(aircraftData.getLong(4) * 1000);
        BasicAircraft bac = new BasicAircraft(
            aircraftData.getString(0),
            aircraftData.getString(1), d,
            coordinate,
            aircraftData.getDouble(9),
            aircraftData.getDouble(10));
        return bac;
    }
}

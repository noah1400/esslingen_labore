package senser;

import org.json.JSONArray;

public class AircraftSentence {
    private JSONArray aircraftData;

    public AircraftSentence(JSONArray aircraftData) {
        this.aircraftData = aircraftData;
    }

    public JSONArray getData() {
        return aircraftData;
    }
}

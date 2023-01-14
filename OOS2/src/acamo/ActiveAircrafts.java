package acamo;

import observer.Observable;
import observer.Observer;

import java.util.ArrayList;
import java.util.HashMap;

import messer.BasicAircraft;

public class ActiveAircrafts implements Observer<BasicAircraft>, ActiveAircraftsInterface {

    private HashMap<String, BasicAircraft> activeAircrafts;

    public ActiveAircrafts() {
        activeAircrafts = new HashMap<String, BasicAircraft>();
    }

    @Override
    public synchronized void store(String icao, BasicAircraft ac) {
        activeAircrafts.put(icao, ac);
    }

    @Override
    public synchronized void clear() {
        activeAircrafts.clear();
    }

    @Override
    public synchronized BasicAircraft retrieve(String icao) {
        BasicAircraft ac = activeAircrafts.get(icao);
        return ac;
    }

    @Override
    public synchronized ArrayList<BasicAircraft> values() {
        ArrayList<BasicAircraft> aircrafts = new ArrayList<>(activeAircrafts.values());
        return aircrafts;
    }

    @Override
    public void update(Observable<BasicAircraft> observable, BasicAircraft newValue) {
        this.store(newValue.getIcao(), newValue);
    }
    
    public String toString() {
        return activeAircrafts.toString();
    }

}

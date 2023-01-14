package acamo;

import java.util.ArrayList;

import messer.BasicAircraft;

public interface ActiveAircraftsInterface {

	public void store(String icao, BasicAircraft ac);

	public void clear();

	public BasicAircraft retrieve(String icao);

	public ArrayList<BasicAircraft> values ();

}

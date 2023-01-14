package senser;

import java.util.ArrayList;
import java.util.List;

import org.json.JSONArray;

import jsonstream.*;
import observer.SimpleObservable;

public class Senser extends SimpleObservable<AircraftSentence> implements Runnable {
	PlaneDataServer server;
	AircraftSentence sentence;

	public Senser(PlaneDataServer server) {
		this.server = server;
	}

	private String getSentence() {
		String list = server.getPlaneListAsString();
		return list;
	}

	public void run() {
		JSONArray planeArray;
		List<AircraftSentence> planelist = new ArrayList<AircraftSentence>();
		AircraftSentenceFactory factory = new AircraftSentenceFactory();
		AircraftSentenceDisplay display = new AircraftSentenceDisplay();

		while (true) {
			planeArray = server.getPlaneArray();

			// Lab1 Manual 3.1
			// System.out.println("Current Aircrafts in range: " + planeArray.length());

			planelist = factory.createSentenceList(planeArray);

			// for (int i = 0; i < planeArray.length(); i++) {
			// planelist.add(factory.createSentence(planeArray.getJSONArray(i)));
			// display.displayData(planelist.get(i));
			// }

			for (AircraftSentence sentence : planelist) {
				setChanged();
				notifyObservers(sentence);
			}
		}
	}
}
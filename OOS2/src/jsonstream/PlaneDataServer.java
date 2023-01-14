package jsonstream;

import java.util.concurrent.LinkedBlockingQueue;
import org.json.*;
import com.github.dvdme.GeoCoordinatesLib.*;

/**
 * @author      Roland Fronczek rofrit01@hs-esslingen.de, Kai Warendorf
 * @version     2.0
 * @since       1.0 (Version von Herrn Warendorf) 
 * 
 * Unter Verwendung der OpenSky API:
 * https://opensky-network.org/apidoc/rest.html
 */
public class PlaneDataServer implements Runnable
{
	StreamingWebClient client;
	private LinkedBlockingQueue<String> jsonQ = new LinkedBlockingQueue<String>();
	private boolean debug = false;
	private boolean exit = false;
	private Double latitude = 0.0;
	private Double longitude = 0.0;
	private int distance = 0;	
	
	public PlaneDataServer(Double lat, Double lon, int dist) {
		client = new StreamingWebClient();
		latitude = lat;
		longitude = lon;
		//set der Distance inklusive Umrechnung in Meter
		distance = dist * 1000;
	}

	/**
	 * Constructor der Klasse PlaneDataServer
	 * Ruft Streaming Webclient auf und empfaengt Daten von der OpenSky API
	 *
	 * @param  url	Uebergabe der URL
	 * @param  lat	latitude des Mittelpunkts
	 * @param  lon 	longitude des Mittelpunkts
	 * @param  dist	Maximale Distanz der zu ermittelnden Flugzeuge
	 */
	public PlaneDataServer(String url, Double lat, Double lon, int dist) {
		client = new StreamingWebClient(url, 1000);
		latitude = lat;
		longitude = lon;
		//set der Distance inklusive Umrechnung in Meter
		distance = dist * 1000;
	}

	public void resetLocation(double lat, double lon, int dist)	{
		jsonQ.clear();
		latitude = lat;
		longitude = lon;
		//set der Distance inklusive Umrechnung in Meter
		distance = dist * 1000;
	}


	public String getJson() {
		String json = null;
		
		try {
			json = jsonQ.take();
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		return json;
	}
	
	/**
	 * Methode zur Ermittlung des Arrays der Flugzeuge
	 * Auch werden die Flugzeuge aus dem Array gefiltert, welche ausserhalb der maximalen Distanz liegen
	 * Verwendet die Klassen Coordinates und CoordinatesCalculations
	 * siehe https://github.com/dvdme/GeoCoordinatesLib.git
	 *
	 * @return returnArray Array mit den gefilterten Flugzeugen
	 */
	public JSONArray getPlaneArray() {
		String json = getJson();
		
		if (json == "429") {
			System.out.println("Too many requests, wait or change your ip!");
			System.exit(1);
		}
		
		JSONObject jsonObject = new JSONObject(json);
		if (debug) System.out.println("jsonObject " + jsonObject);
		JSONArray planeArray = jsonObject.getJSONArray("states");
		JSONArray returnArray = new JSONArray();
		Coordinates coord = new Coordinates(latitude, longitude);
		for(int i = 0 ; i < planeArray.length() ; i++) {
			JSONArray tempArray = (JSONArray) planeArray.get(i);
			try {
				//System.out.println(tempArray.get(6) + "   " + tempArray.get(5));
				Coordinates tempCoord = new Coordinates((Double) tempArray.get(6),(Double) tempArray.get(5));
				if(CoordinatesCalculations.isInCircleArea(tempCoord, coord, distance)) {
					returnArray.put(tempArray);
				}
			}catch(ClassCastException e) {}
		}
		if (debug) System.out.println("planeArray " + planeArray.length() + "  " + planeArray);
		return returnArray;
	}
	
	public String getPlaneListAsString() {
		String list = getPlaneArray().toString(); 
		if(list.length() > 5)
			return list.substring(1, list.length() - 1);
		else 
			return dummyPlanes();
	}
	
	/**
	 * Methode zur Rueckgabe von Dummydaten
	 * Wird verwendet, wenn das planeArray nicht gefuellt ist
	 *
	 * @return returnArray Array mit den gefilterten Flugzeugen
	 */
	private String dummyPlanes() {
		String dummies = "[\"4ca511\",\"RYR71DK \",\"Ireland\",1515089860,1515089860,9.0687,48.5482,10668,false,248.43,138.02,0,null,10584.18,\"2515\",false,0],[\"4b16b9\",\"SWR828  \",\"Switzerland\",1515089860,1515089860,9.5105,49.3268,10363.2,false,200.47,3.38,0.33,null,10264.14,\"1000\",false,0],[\"3c6749\",\"DLH8K   \",\"Germany\",1515089860,1515089860,8.6731,48.1555,9745.98,false,242.73,26.02,0,null,9723.12,\"1000\",false,0],[\"3c674e\",\"DLH7HW  \",\"Germany\",1515089860,1515089860,9.6777,49.3146,7376.16,false,243.15,132.94,8.78,null,7284.72,\"7601\",false,0],[\"4b1a3e\",\"EZS4640 \",\"Switzerland\",1515089860,1515089860,8.988,48.3083,9037.32,false,225.62,23.23,6.5,null,8976.36,\"1000\",false,0]"
				+ ",[\"405d0f\",\"EZY12YQ \",\"United Kingdom\",1515089860,1515089860,9.9079,49.3371,9723.12,false,267.64,132.43,-14.63,null,9646.92,\"4737\",false,0],[\"3c6489\",\"DLH64M  \",\"Germany\",1515089860,1515089860,9.0985,48.9544,7414.26,false,240.88,10.09,-8.13,null,7360.92,\"1000\",false,0],[\"3c6449\",\"DLH255  \",\"Germany\",1515089860,1515089860,8.9655,47.9128,9136.38,false,202.29,358.11,0,null,9121.14,\"1000\",false,0],[\"4ca2d4\",\"RYR89SQ \",\"Ireland\",1515089860,1515089860,9.4972,48.0567,11894.82,false,267.36,129.85,-0.33,null,11788.14,\"2711\",false,0],[\"4ca2fe\",\"RYR4854 \",\"Ireland\",1515089860,1515089860,8.8782,48.6076,11277.6,false,244.77,143.2,0,null,11178.54,\"3143\",false,0],"
				+ "[\"405633\",\"EZY96ZR \",\"United Kingdom\",1515089859,1515089860,8.2042,48.3898,10683.24,false,230.9,167.39,0,null,10599.42,\"1000\",false,0],[\"4ca1b8\",\"RYR45KR \",\"Ireland\",1515089860,1515089860,9.0715,48.2769,11277.6,false,259.85,128,0.33,null,11209.02,\"2733\",false,0],[\"3c6dd0\",\"EWG32H  \",\"Germany\",1515089860,1515089860,9.3003,48.6107,4389.12,false,206.3,90.57,11.7,null,4267.2,\"7653\",false,0],[\"3003ad\",\"DLH6NH  \",\"Italy\",1515089860,1515089860,9.1009,48.0406,10447.02,false,211.83,356.52,-7.15,null,10454.64,\"0267\",false,0],[\"3c085a\",\"SDR3173 \",\"Germany\",1515089860,1515089860,9.3794,49.0589,10972.8,false,233.52,19.83,0,null,10873.74,\"2335\",false,0],"
				+ "[\"3c49ce\",\"EWG8FC  \",\"Germany\",1515089779,1515089783,9.1968,48.6879,null,true,0,165,null,null,null,null,false,0],[\"3c49b6\",\"EWG59C  \",\"Germany\",1515089859,1515089860,8.5862,48.2098,5768.34,false,198.7,184.6,-3.25,null,5715,\"1133\",false,0],[\"342105\",\"IBS3665 \",\"Spain\",1515089859,1515089859,8.5677,48.3067,5486.4,false,180.79,224.88,0.33,null,5440.68,\"0620\",false,0]"; 
		return dummies;
	}


	public void run() {
		while (!exit)
		{
			String json = client.readJSON();
			if (debug) System.out.println("Sentence " + json + "\n\n\n");
			// add complete json to queue
			jsonQ.add(json);
		}
	}
	
	public void stop() {
		exit = true;
		client.stop();
	}
}
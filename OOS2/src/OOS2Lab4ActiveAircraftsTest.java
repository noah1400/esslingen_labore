import java.util.ArrayList;

import acamo.ActiveAircrafts;
import jsonstream.*;
import messer.BasicAircraft;
import messer.Messer;
import senser.Senser;

public class OOS2Lab4ActiveAircraftsTest
{
    private static double latitude = 48.7433425;
    private static double longitude = 9.3201122;
    private static boolean haveConnection = true;

	public static void main(String[] args)
	{
		String urlString = "https://opensky-network.org/api/states/all";
		PlaneDataServer server;
		
		if(haveConnection)
			server = new PlaneDataServer(urlString, latitude, longitude, 150);
		else
			server = new PlaneDataServer(latitude, longitude, 100);

		Senser senser = new Senser(server);
		new Thread(server).start();
		new Thread(senser).start();
		
		Messer messer = new Messer();
		senser.addObserver(messer);
		new Thread(messer).start();
		
		ActiveAircrafts activeAircrafts = new ActiveAircrafts();
		messer.addObserver(activeAircrafts);
		
		while(true) {
			System.out.println("Sleeping for 2 seconds");
			try {
				Thread.sleep(2000);
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
			ArrayList<BasicAircraft> aircrafts = activeAircrafts.values();
			
			System.out.println("Aircrafts in Hashtable " + aircrafts.size());
			for(BasicAircraft ba : aircrafts) {
				System.out.println(ba);
			}
		}
		
		
		// put this into comments while testing the hashtable alone
		/*
		BasicAircraft ba1 = aircrafts.get(0);

		System.out.println("\nData for Aircraft  " + ba1.getIcao());
		ArrayList<String> attributesNames = BasicAircraft.getAttributesNames();
		ArrayList<Object> attributesValues = BasicAircraft.getAttributesValues(ba1);
		for(int i = 0;i < attributesNames.size();i++) {
			System.out.println("Name " + attributesNames.get(i) + "\tValue " + attributesValues.get(i));
		}
		*/

	}
}
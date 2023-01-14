import jsonstream.*;
import messer.Messer;
import senser.Senser;

public class OOS2Lab2Starter
{
    private static double latitude = 48.7433;
    private static double longitude = 9.3201;
    private static boolean haveConnection = true;

	public static void main(String[] args)
	{
		String urlString = "https://opensky-network.org/api/states/all";
		PlaneDataServer server;
		
		if(haveConnection)
			server = new PlaneDataServer(urlString, latitude, longitude, 100);
		else
			server = new PlaneDataServer(latitude, longitude, 150);

		Senser senser = new Senser(server);
		new Thread(server).start();
		new Thread(senser).start();

		Messer messer = new Messer();
		senser.addObserver(messer);
		new Thread(messer).start();
	}
}
package jsonstream;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.InputStreamReader;
import java.net.*;
import java.util.concurrent.LinkedBlockingQueue;

import javax.net.ssl.HostnameVerifier;
import javax.net.ssl.HttpsURLConnection;
import javax.net.ssl.SSLContext;
import javax.net.ssl.SSLSession;
import javax.net.ssl.TrustManager;
import javax.net.ssl.X509TrustManager;

import java.security.cert.X509Certificate;

public class StreamingWebClient {
	private boolean exit = false;
	private String basicurl = null;
	private String url;
	private LinkedBlockingQueue<String> q;
	private HttpsURLConnection c = null;
	Runnable producer = null;

	public StreamingWebClient() {
		String line;
		q = new LinkedBlockingQueue<String>();
		System.err.println("Using file: jsonsky.txt");
		try {
			BufferedReader br = new BufferedReader(new FileReader("jsonsky.txt"));
			do {
				line = br.readLine();
				//System.out.println(line);
				if(line != null)
					q.add(line);
			} while (line != null);
			br.close();
		} catch (Exception io) {
			io.printStackTrace();
		}
	}

	public StreamingWebClient(String urlstr, int timeout) {
		
		url = urlstr;

		// realization of the observable pattern via queue
		q = new LinkedBlockingQueue<String>(1);
		System.err.println(this.getClass().getName() + ": Connecting to " + url);
		// make a producer thread that fills a queue
		producer = new Runnable() {
			public void run() {
				String json;

				while (!exit) 
				{
					try {
						/* Start of Fix */
						TrustManager[] trustAllCerts = new TrustManager[] { new X509TrustManager() {
							public java.security.cert.X509Certificate[] getAcceptedIssuers() { return null; }
							public void checkClientTrusted(X509Certificate[] certs, String authType) { }
							public void checkServerTrusted(X509Certificate[] certs, String authType) { }

						} };

						SSLContext sc = SSLContext.getInstance("SSL");
						sc.init(null, trustAllCerts, new java.security.SecureRandom());
						HttpsURLConnection.setDefaultSSLSocketFactory(sc.getSocketFactory());

						// Create all-trusting host name verifier
						HostnameVerifier allHostsValid = new HostnameVerifier() {
							public boolean verify(String hostname, SSLSession session) { return true; }
						};
						// Install the all-trusting host verifier
						HttpsURLConnection.setDefaultHostnameVerifier(allHostsValid);
						/* End of the fix*/

						// System.out.println(url);
						URL u = new URL(url);
						c = (HttpsURLConnection) u.openConnection();
						c.setRequestMethod("GET");
						c.setRequestProperty("Content-length", "0");
						c.setRequestProperty("User-Agent", "Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.95 Safari/537.11");

						c.setUseCaches(false);
						c.setAllowUserInteraction(false);
						c.setConnectTimeout(timeout);
						c.setReadTimeout(timeout);
						c.connect();

						Integer status = c.getResponseCode();

						switch (status) {
						case 200:
						case 201:
							BufferedReader br = new BufferedReader(new InputStreamReader(c.getInputStream()));
							StringBuilder sb = new StringBuilder();
							String line;
							while ((line = br.readLine()) != null) {
								sb.append(line);//+"\n");
							}
							json =  sb.toString();
							break;
						default: 
							json =  status.toString();
						}
					} catch (Exception ex) {
						continue;
					}
					// System.out.println(json);
					q.add(json);
					try {
						//RF: Aenderung auf 10 Sekunden 
						Thread.sleep(5000);
					} catch (InterruptedException e) {}
					c.disconnect();
				}
			} // run
		}; // producer thread
		new Thread(producer).start();
	} // constructor

	public String readJSON() {
		String json = null;
		// consumes the queue
		try {
			json = q.take();
		} catch (Exception e) {
		}
		//System.out.println(json);
		return json;
	} // readJSON
	
	public void stop() {
		exit = true;
	}

	
} // class
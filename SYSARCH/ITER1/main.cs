using System;
using System.Collections.Generic;

namespace ZwischenhaendlerApp
{
    class Program
    {
        static void Main(string[] args)
        {
            List<Zwischenhaendler> haendlerListe = new List<Zwischenhaendler>();

            Console.WriteLine("Wie viele Zwischenhändler nehmen teil?");
            int anzahlTeilnehmer;
            while (!int.TryParse(Console.ReadLine(), out anzahlTeilnehmer) || anzahlTeilnehmer <= 0)
            {
                Console.WriteLine("Bitte geben Sie eine gültige Anzahl ein:");
            }

            for (int i = 1; i <= anzahlTeilnehmer; i++)
            {
                Console.WriteLine($"Name des {i}. Zwischenhändlers:");
                string haendlerName = Console.ReadLine();

                Console.WriteLine($"Firmenname von {haendlerName}:");
                string firmaName = Console.ReadLine();

                haendlerListe.Add(new Zwischenhaendler { Name = haendlerName, FirmenName = firmaName });
            }

            // Tageszähler initialisieren
            int aktuellerTag = 1;

            // Runden der Zwischenhändler starten
            int aktuellerHaendlerIndex = 0;
            while (true) // Hauptspiel-Schleife
            {
                Zwischenhaendler aktuellerHaendler = haendlerListe[aktuellerHaendlerIndex];
                Console.WriteLine($"{aktuellerHaendler.Name} von {aktuellerHaendler.FirmenName} | Tag {aktuellerTag}");
                Console.WriteLine("b) Runde beenden");

                if (Console.ReadLine() == "b")
                {
                    aktuellerHaendlerIndex++;
                    if (aktuellerHaendlerIndex >= anzahlTeilnehmer)
                    {
                        aktuellerTag++; // Tageszähler erhöhen, wenn alle Händler ihre Runde beendet haben
                        aktuellerHaendlerIndex = 0; // HaendlerIndex für den nächsten Tag zurücksetzen
                    }
                }
                else
                {
                    Console.WriteLine("Ungültige Eingabe, bitte geben Sie 'b' ein, um die Runde zu beenden.");
                }
            }
        }

        class Zwischenhaendler
        {
            public string Name { get; set; }
            public string FirmenName { get; set; }
        }
    }
}
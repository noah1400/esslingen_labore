using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace ZwischenhaendlerApp
{
    class Program
    {
        private const double RABATT = 0.8;
        static void Main(string[] args)
        {
            List<Produkt> produkte = LeseProdukteAusDatei("produkte.yml");
            List<Zwischenhaendler> haendler = InitialisiereHaendler();

            int aktuellerTag = 1;
            int aktuellerHaendlerIndex = 0;

            while (true) // Hauptspiel-Schleife
            {
                Zwischenhaendler aktuellerHaendler = haendler[aktuellerHaendlerIndex];
                ZeigeMenu(aktuellerHaendler, aktuellerTag);

                string eingabe = Console.ReadLine();
                switch (eingabe)
                {
                    case "e":
                        Einkaufen(aktuellerHaendler, produkte);
                        break;
                    case "v":
                        Verkaufen(aktuellerHaendler);
                        break;
                    case "b":
                        aktuellerHaendlerIndex++;
                        if (aktuellerHaendlerIndex >= haendler.Count)
                        {
                            RotateZwischenhaendlers(haendler);
                            aktuellerHaendlerIndex = 0;
                            aktuellerTag++;
                        }
                        break;
                }
            }
        }

        static void RotateZwischenhaendlers(List<Zwischenhaendler> haendler)
        {
            if (haendler.Count > 0)
            {
                var first = haendler[0];
                haendler.RemoveAt(0);
                haendler.Add(first);
            }
        }


        static List<Zwischenhaendler> InitialisiereHaendler()
        {
            List<Zwischenhaendler> haendler = new List<Zwischenhaendler>();
            Console.WriteLine("Wie viele Zwischenhändler nehmen teil?");
            int anzahlHaendler;
            while (!int.TryParse(Console.ReadLine(), out anzahlHaendler) || anzahlHaendler <= 0)
            {
                Console.WriteLine("Bitte geben Sie eine gültige Anzahl ein:");
            }

            for (int i = 1; i <= anzahlHaendler; i++)
            {
                Console.WriteLine($"Name des {i}. Zwischenhändlers:");
                string haendlerName = Console.ReadLine();

                Console.WriteLine($"Firmenname von {haendlerName}:");
                string firmaName = Console.ReadLine();

                Console.WriteLine($"Schwierigkeitsgrad (a) Einfach - $15,000, (b) Normal - $10,000, (c) Schwer - $7,000:");
                int startKontostand = 0;
                switch (Console.ReadLine().ToLower())
                {
                    case "a": startKontostand = 15000; break;
                    case "b": startKontostand = 10000; break;
                    case "c": startKontostand = 7000; break;
                }

                haendler.Add(new Zwischenhaendler { Name = haendlerName, FirmenName = firmaName, Kontostand = startKontostand });
            }
            return haendler;
        }

        static void ZeigeMenu(Zwischenhaendler haendler, int tag)
        {
            Console.WriteLine($"{haendler.Name} von {haendler.FirmenName} | ${haendler.Kontostand} | Tag {tag}");
            Console.WriteLine("e) Einkaufen");
            Console.WriteLine("v) Verkaufen");
            Console.WriteLine("b) Runde beenden");
        }

        static void Einkaufen(Zwischenhaendler haendler, List<Produkt> produkte)
        {
            ZeigeVerfuegbareProdukte(produkte);

            int auswahl;
            if (int.TryParse(Console.ReadLine(), out auswahl) && auswahl >= 1 && auswahl <= produkte.Count)
            {
                KaufeProdukt(haendler, produkte[auswahl - 1]);
            }
        }

        static void ZeigeVerfuegbareProdukte(List<Produkt> produkte)
        {
            Console.WriteLine("Verfügbare Produkte:");
            for (int i = 0; i < produkte.Count; i++)
            {
                Console.WriteLine($"{i + 1}) {produkte[i].Name} ({produkte[i].Durability} Tage) ${produkte[i].BasePrice}/Stück");
            }
            Console.WriteLine("z) Zurück");
        }

        static void KaufeProdukt(Zwischenhaendler haendler, Produkt gewaehltesProdukt)
        {
            Console.WriteLine($"Wieviel von {gewaehltesProdukt.Name} kaufen?");
            int menge;
            if (int.TryParse(Console.ReadLine(), out menge) && menge > 0)
            {
                int gesamtpreis = menge * gewaehltesProdukt.BasePrice;
                if (haendler.Kontostand >= gesamtpreis)
                {
                    haendler.Kontostand -= gesamtpreis;
                    if (haendler.GekaufteProdukte.ContainsKey(gewaehltesProdukt))
                    {
                        haendler.GekaufteProdukte[gewaehltesProdukt] += menge;
                    }
                    else
                    {
                        haendler.GekaufteProdukte[gewaehltesProdukt] = menge;
                    }
                }
                else
                {
                    Console.WriteLine("Nicht genug Geld für den Kauf.");
                }
            }
        }


        static void Verkaufen(Zwischenhaendler haendler)
        {
            ZeigeBesitzProdukte(haendler);

            int auswahl;
            if (int.TryParse(Console.ReadLine(), out auswahl) && auswahl >= 1 && auswahl <= haendler.GekaufteProdukte.Count)
            {
                VerkaufeProdukt(haendler, haendler.GekaufteProdukte.Keys.ElementAt(auswahl - 1));
            }
        }

        static void ZeigeBesitzProdukte(Zwischenhaendler haendler)
        {
            Console.WriteLine("Produkte im Besitz:");
            int i = 1;
            foreach (var gekauftesProdukt in haendler.GekaufteProdukte)
            {
                int verkaufspreis = (int)Math.Round(gekauftesProdukt.Key.BasePrice * RABATT);
                Console.WriteLine($"{i}) {gekauftesProdukt.Key.Name} ({gekauftesProdukt.Value}) ${verkaufspreis}/Stück");
                i++;
            }
            Console.WriteLine("z) Zurück");
        }

        static void VerkaufeProdukt(Zwischenhaendler haendler, Produkt produktZumVerkauf)
        {
            Console.WriteLine($"Wieviel von {produktZumVerkauf.Name} verkaufen (max. {haendler.GekaufteProdukte[produktZumVerkauf]})?");
            int menge;
            if (int.TryParse(Console.ReadLine(), out menge) && menge > 0)
            {
                int verkaufspreisProStueck = (int)Math.Round(produktZumVerkauf.BasePrice * RABATT);
                int gesamtpreis = menge * verkaufspreisProStueck;
                haendler.Kontostand += gesamtpreis;
                haendler.GekaufteProdukte[produktZumVerkauf] -= menge;
                if (haendler.GekaufteProdukte[produktZumVerkauf] <= 0)
                {
                    haendler.GekaufteProdukte.Remove(produktZumVerkauf);
                }
            }
        }


        static List<Produkt> LeseProdukteAusDatei(string dateiname)
        {
            List<Produkt> produkte = new List<Produkt>();
            string[] zeilen = File.ReadAllLines(dateiname);
            Produkt currentProdukt = null;

            foreach (string zeile in zeilen)
            {
                string trimmedZeile = zeile.Trim();
                if (trimmedZeile.StartsWith("- name: "))
                {
                    currentProdukt = new Produkt { Name = trimmedZeile.Substring("- name: ".Length).Trim() };
                    produkte.Add(currentProdukt);
                }
                else if (currentProdukt != null && trimmedZeile.StartsWith("durability: "))
                {
                    currentProdukt.Durability = int.Parse(trimmedZeile.Substring("durability: ".Length).Trim());
                }
                else if (currentProdukt != null && trimmedZeile.StartsWith("baseprice: "))
                {
                    currentProdukt.BasePrice = int.Parse(trimmedZeile.Substring("baseprice: ".Length).Trim());
                }
            }

            return produkte;
        }

    }

    class Produkt
    {
        public string Name { get; set; }
        public int Durability { get; set; }
        public int BasePrice { get; set; }
    }

    class Zwischenhaendler
    {
        public string Name { get; set; }
        public string FirmenName { get; set; }
        public int Kontostand { get; set; }
        public Dictionary<Produkt, int> GekaufteProdukte = new Dictionary<Produkt, int>();
    }
}

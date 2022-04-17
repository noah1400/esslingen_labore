import pandas as pd
import dataframe_image as dfi

def readData(filename):
    # Daten einlesen
    df = pd.read_csv(filename,
                           sep=';',
                           header=None,
                           names=['Personalnummer', 
                                    'Anrede', 
                                    'Vorname', 
                                    'Nachname',
                                    'Geburtsdatum'],
                            encoding='latin-1') # encoding auf latin-1 da sonst probleme mit Umlauten
    return df

def is_valid_year(year: str):
    # Testen ob Jahr valide ist
    if year.isdigit() and len(year) == 4:
        if int(year) > 1900 and int(year) < 2006:
            return True
    return False

def is_correctable(birthday):
    # Prüfen ob Datum korrigierbar ist
    if isinstance(birthday, str):
        months = ['Januar','Februar', 'März', 'April', 'Mai', 'Juni', 'Juli', 'August', 'September', 'Oktober', 'November', 'Dezember']
        for m in months:
            if m in birthday:
                new_str = birthday.split(m)[1]
                years = [x for x in new_str.split(' ') if x.isdigit()]
                for year in years:
                    if is_valid_year(year):
                        return months.index(m) + 1, year
                return months.index(m) + 1, None
    return None, None


def get_error_types_and_clean(errorframe, fullframe):
    
    # Erstelle ein neues Dataframe mit den Fehlertypen

    for index, row in errorframe.iterrows():
        birthday = row['Geburtsdatum']
        month, year = is_correctable(birthday)
        if month is not None and year is not None:
            datensatz = 'Korrektur'
            typ = 'Monat reicht für Alter'
        elif month is not None:
            datensatz = 'Löschen'
            typ = 'Jahr fehlt'
        elif year is not None:
            datensatz = 'Löschen'
            typ = 'Monat fehlt'
        else:
            datensatz = 'Löschen'
            typ = 'Kein Datum'

        errorframe.loc[index, 'Datensatz?'] = datensatz
        errorframe.loc[index, 'Typ'] = typ


        # Entferne/Korrigiere Datensätze
        if datensatz == 'Löschen':
            fullframe = fullframe.drop(index)
        elif datensatz == 'Korrektur':
            fullframe.loc[index,'Geburtsdatum'] = '01.' + str(month) + '.' + str(year)

    return fullframe, errorframe


def clean(data):
    errorframe = data[pd.to_datetime(data['Geburtsdatum'], format='%d.%m.%Y',errors='coerce').isna()]
    cleaned, err = get_error_types_and_clean(errorframe, data)
    
    print(err)
    return cleaned

def get_gender_based_birthdays(data, gender=None):
    # Alle Geburtsdaten des angegebenen Geschlechts
    # Wenn kein Geschlecht angegeben ist gibt diese Funktion alle Geburtstage zurück
    if gender is not None:
        data = data[data['Anrede'] == gender]
    age = data['Geburtsdatum'].apply(lambda x: 2005 - int(x.split('.')[2]))
    return age

def age_average(data):
    # Berechne durchschnittliches Alter
    return data.mean()

def age_variance(data):
    # Berechne altersvarianz
    variance = data.var()
    return variance
    
def age_standard_deviation(data):
    # Berechne Standadabweichung
    return data.std()

def get_median(data):
    # Berechne Median
    return data.median()

def get_range(data):
    # Berechne Range
    print('Maximum ', data.max())
    print('Minimum ', data.min())
    return data.max() - data.min()
    
dt = readData('data/sr_aufg_1_35.txt')
dt_clean = clean(dt)

upper_limit = 2005
lower_limit = 2005-20
age_0_20 = dt_clean[lambda x: x['Geburtsdatum'].apply(lambda y: int(y.split('.')[2]) >= lower_limit and int(y.split('.')[2]) <= upper_limit)]


upper_limit = 2005 - 21
lower_limit = 2005 - 30
age_20_30 = dt_clean[lambda x: x['Geburtsdatum'].apply(lambda y: int(y.split('.')[2]) >= lower_limit and int(y.split('.')[2]) <= upper_limit)]

upper_limit = 2005 - 31
lower_limit = 2005 - 40
age_30_40 = dt_clean[lambda x: x['Geburtsdatum'].apply(lambda y: int(y.split('.')[2]) >= lower_limit and int(y.split('.')[2]) <= upper_limit)]

upper_limit = 2005 - 41
lower_limit = 2005 - 50
age_40_50 = dt_clean[lambda x: x['Geburtsdatum'].apply(lambda y: int(y.split('.')[2]) >= lower_limit and int(y.split('.')[2]) <= upper_limit)]

lower_limit = 2005 - 51
age_50 = dt_clean[lambda x: x['Geburtsdatum'].apply(lambda y: int(y.split('.')[2]) >= lower_limit)]

gbb = get_gender_based_birthdays(dt_clean,'Herr')
male_average = age_average(gbb)
male_variance = age_variance(gbb)
male_standard_deviation = age_standard_deviation(gbb)
male_median = get_median(gbb)
male_range = get_range(gbb)

gbb = get_gender_based_birthdays(dt_clean, 'Frau')
female_average = age_average(gbb)
female_variance = age_variance(gbb)
female_standard_deviation = age_standard_deviation(gbb)
female_median = get_median(gbb)
female_range = get_range(gbb)

gbb = get_gender_based_birthdays(dt_clean)
average = age_average(gbb)
variance = age_variance(gbb)
standard_deviation = age_standard_deviation(gbb)
median = get_median(gbb)
rng = get_range(gbb)

dat = [ {average, female_average, male_average},
        {variance, female_variance, male_variance},
        {standard_deviation, female_standard_deviation, male_standard_deviation},
        {median, female_median, male_median},
        {rng, female_range, male_range} ]

dataf = pd.DataFrame(dat, columns=['gesamt', 'Frauen', 'Männer'], 
        index=['Mittelwert', 'Varianz', 'Std.-Abw', 'Median', 'Spannweite'])

print(dataf)
dfi.export(dataf.style, "out.png")
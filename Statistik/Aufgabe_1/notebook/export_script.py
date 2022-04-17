# %%
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
from datetime import datetime

# %%
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

# %%
def is_valid_year(year: str):
    # Testen ob Jahr valide ist
    if year.isdigit() and len(year) == 4:
        if int(year) > 1900 and int(year) < 2006:
            return True
    return False

# %%
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

# %%
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

# %%
def clean(data):
    errorframe = data.loc[pd.to_datetime(data['Geburtsdatum'], format='%d.%m.%Y',errors='coerce').isna(), ['Personalnummer', 
                                    'Anrede', 
                                    'Vorname', 
                                    'Nachname',
                                    'Geburtsdatum']]
    cleaned, err = get_error_types_and_clean(errorframe, data)
    return cleaned, err

# %%
def from_dob_to_age(dob):
    st = datetime(2005,12,31)
    #st = datetime.today()
    a = st.year - dob.year - ((st.month, st.day) < (dob.month, dob.day))
    return a

def get_gender_based_birthdays(data, gender=None):
    # Alle Geburtsdaten des angegebenen Geschlechts
    # Wenn kein Geschlecht angegeben ist gibt diese Funktion alle Geburtstage zurück
    if gender is not None:
        data = data[data['Anrede'] == gender]
    
    # Alter ausrechnen
    
    age = pd.DataFrame(columns=['age'])

    age['age'] = pd.to_datetime(data['Geburtsdatum'], format="%d.%m.%Y").apply(lambda x: from_dob_to_age(x))

    
    return age

# %%
def age_average(data):
    # Berechne durchschnittliches Alter
    return data['age'].mean()

def age_variance(data):
    # Berechne altersvarianz
    variance = data['age'].var()
    return variance
    
def age_standard_deviation(data):
    # Berechne Standadabweichung
    return data['age'].std()

def get_median(data):
    # Berechne Median
    return data['age'].median()

def get_range(data):
    # Berechne Range
    return data['age'].max() - data['age'].min()

# %%
dt = readData('sr_aufg_1_35.txt')

# %%
dt_clean, err = clean(dt)

# %%
err.style

# %%
gbb = get_gender_based_birthdays(dt_clean,'Herr')
male_average = age_average(gbb)
male_variance = age_variance(gbb)
male_standard_deviation = age_standard_deviation(gbb)
male_median = get_median(gbb)
male_range = get_range(gbb)
male_a020 = gbb[gbb['age'].apply(lambda y: y >= 0 and y < 20)]
male_a2030 = gbb[gbb['age'].apply(lambda y: y >= 20 and y < 30)]
male_a3040 = gbb[gbb['age'].apply(lambda y: y >= 30 and y < 40)]
male_a4050 = gbb[gbb['age'].apply(lambda y: y >= 40 and y < 50)]
male_a50 = gbb[gbb['age'].apply(lambda y: y >= 50)]
male_all = gbb['age']

gbb = get_gender_based_birthdays(dt_clean, 'Frau')
female_average = age_average(gbb)
female_variance = age_variance(gbb)
female_standard_deviation = age_standard_deviation(gbb)
female_median = get_median(gbb)
female_range = get_range(gbb)
female_a020 = gbb[gbb['age'].apply(lambda y: y >= 0 and y < 20)]
female_a2030 = gbb[gbb['age'].apply(lambda y: y >= 20 and y < 30)]
female_a3040 = gbb[gbb['age'].apply(lambda y: y >= 30 and y < 40)]
female_a4050 = gbb[gbb['age'].apply(lambda y: y >= 40 and y < 50)]
female_a50 = gbb[gbb['age'].apply(lambda y: y >= 50)]
female_all = gbb['age']

gbb = get_gender_based_birthdays(dt_clean)
average = age_average(gbb)
variance = age_variance(gbb)
standard_deviation = age_standard_deviation(gbb)
median = get_median(gbb)
rng = get_range(gbb)



# %%
dat = [ {average, female_average, male_average},
        {variance, female_variance, male_variance},
        {standard_deviation, female_standard_deviation, male_standard_deviation},
        {median, female_median, male_median},
        {rng, female_range, male_range} ]

# %%
dataf = pd.DataFrame(dat, columns=['gesamt', 'Frauen', 'Männer'], 
        index=['Mittelwert', 'Varianz', 'Std.-Abw', 'Median', 'Spannweite'])

# %%
dataf.style

# %%
labels = np.array(['(0,20]','(20,30]','(30,40]','(40,50]','(50,]'])
male = np.array([
    len(male_a020.index),
    len(male_a2030.index),
    len(male_a3040.index),
    len(male_a4050.index),
    len(male_a50.index)
])
female = np.array([
    len(female_a020.index),
    len(female_a2030.index),
    len(female_a3040.index),
    len(female_a4050.index),
    len(female_a50.index)
])
x = np.arange(len(labels))
width = 0.35
fig, ax = plt.subplots()
rect1 = ax.bar(x-width/2,male,width,label="Männer")
rect2 = ax.bar(x+width/2,female,width,label="Frauen")

ax.set_ylabel("Häufigkeit")
ax.set_title("Altersverteilung zum Stichtag 31.12.2005")
ax.set_xticks(x)
ax.set_xticklabels(labels)
ax.legend()

#ax.bar(rect1, padding=6)
#ax.bar(rect2, padding=6)

fig.tight_layout()

plt.show()

# %%
male_all_count = len(male_all)
labels = ['(0,20]','(20,30]','(30,40]','(40,50]','(50,]']
sizes = [
        len(male_a020)/male_all_count*100,
        len(male_a2030)/male_all_count*100,
        len(male_a3040)/male_all_count*100,
        len(male_a4050)/male_all_count*100,
        len(male_a50)/male_all_count*100
        ]

fig1, ax1 = plt.subplots()
ax1.pie(sizes,labels=labels, autopct='%1.1f%%',
        startangle=90)
ax1.axis('equal')
plt.title("Altersverteilung Männer")
plt.show()

# %%
female_all_count = len(female_all)
sizes = [
        len(female_a020)/female_all_count*100,
        len(female_a2030)/female_all_count*100,
        len(female_a3040)/female_all_count*100,
        len(female_a4050)/female_all_count*100,
        len(female_a50)/female_all_count*100
        ]
fig1, ax1 = plt.subplots()
ax1.pie(sizes,labels=labels, autopct='%1.1f%%',
        startangle=90)
ax1.axis('equal')
plt.title("Altersverteilung Frauen")
plt.show()



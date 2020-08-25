# Gintaro staklės
Programa skirta obliavimo/frezavimo auksčiui atvaizduoti.

## Staklių auksčio nustatymo veikimo logika
Prie staklių pakėlimo variklio ašies pritvirtinome iš skardos pagamintą apskritą diską su 8 iškirptais tarpais jame.
Šalia disko sumontuotais InfraRed sensoriais (be jokio fizinio kontakto) yra nustatoma ašies posūklio kryptis ir pasisukimų skaičius.
Šis pasisukimų skaičius yra išverčiamas į milimetus ir suapvalintas iki 1/10 milimetro parodomas staklių panelėje sumontuotame ekrane.
Reikalui esant, šalia ekrano yra sumontuoti du mygtukai TOP ir DOWN. Jų pagalba galima sukalibruoti įrenginio atmintyje saugomą aukštį.

**Prengtas techninis sprendimas nustato aukštį 0.0125mm tikslumu!**


### Techninis aprašymas
Su C++ parašyta aplikacija veikia Arduino Nano kontroleryje.
Prie Arduino Nano prijungti tokie sensoriai:
- Display - skirtas auksčio atvaizdavimui milimetrais su 1/10 milimetro tisklumu.
- Mygtukai: TOP ir DOWN. Jie skirti programos atmintyje saugomam auksčiui sukalibruoti.
- Encoderis - http://www.pjrc.com/teensy/td_libs_Encoder.html


Kad elektrai dingus, nedingtu atmintyje saugomo auksčio parodymai, jie yra išsaugomi į EEPROM atminti.
Tam, kad taupyti EEPROM atminties resursą, buvo padaryti keli apsaugos sprendimai:
 - 5s užlaikymas po auksčio pasikeitimo. Kad vykdant auksčio pasikeitimą, nevyktu rašymas į EEPROM kelis kartus.
 - kas 10`000 EEPROM ciklų, panaudojamas sekantis atminties blokas. Nes kiekvienas EEPROM atminties blokas turi įrašymo ciklų limitą.

### Tobulintinos vietos:
- Padaryti saugojimą į EEPROM, tik dingus elektrai. Tam reikėtu su kondensatorių pagalba užtikrinti darbinę įtampą bent 100ms trukmei.
Įrašymui į EEPROM užtenka ~20ms. Atitinkamai, reikia implementuoti įtampos kritimo detektavimą per GPIO.

- Dar galima būtu patobulinti kalibravimo mygtukų TOP/DOWN jautrumą. Įvertinant paspaudimo trukmę ir t.t.

### Neišnaudotos galimybės
- Nesudėtinga padaryti staklių aukščio valdymą iš Arduino Nano kontrolerio. Pajungus variklį valdančius mygtukus prie relių, kurias valdytu kontroleris.


**Nauda būtu tokia:**
aukščio pakėlimas ir nuleidimas vyktu tiksiai pagal užduotus parodymus ekrane. Nebereikėtu žmogui spaudyti variklio valdymo mygtukų po kelis kartus, kad pasiekti tikslų norimą aukštį.

Valdymo pvz.:
Nustačius ekrane norimą aukštį (1/10 milimetro tikslumu), galima būtu paleisti kontroleryje komandą. Ji aktyvuotu reikalingą relę ir variklis pakeistu staklių darbinį aukštį iki nurodyto lygio.

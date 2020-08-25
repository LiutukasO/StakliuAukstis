# Gintaro stakles
Programa skirta obliavimo/frezavimo auksčiui atvaizduoti.

## Staklių auksčio nustatymo veikimo logika
Prie staklių pakėlimo variklio ašies pritvirtinome iš skardos pagamintą apskritą diską su 8 iškirptais tarpais jame.
Šalia disko sumontuoti InfraRed sensorių pagalba (be jokio fizinio kontakto) yra nustatoma ašies posūklio kryptis ir pasisukimų skaičius.
Šis pasisukimų skaičių išverčiamas į milimetus 1/10 tikslumu ir parodomas staklių panelėje sumontuotame ekrane.
Reikalui esant, šalia ekrano yra sumontuoti du mygtukai TOP, DOWN. Jų pagalba galima sukalibruoti įrenginio atmintyje saugomą aukštį.


### Techninis aprašymas
Su C++ parašyta aplikacija veikia Arduino Nano pagrindu.
Prie Arduino Nano prijungti tokie sensoriai:
- Display - skirtas auksčio atvaizdavimui milimetrais su 1/10 milimetro tisklumu.
- Mygtukai: TOP, DOWN. Jie skirti programos atmintyje saugomam auksčiui sukalibruoti.
- Encoderis.

Kad elektrai dingus, nedingtu atmintyje saugomo auksčio parodymai, jie yra išsaugomi į EEPROM atminti.
Tam, kad taupyti EEPROM atminties resursą, buvo padaryti keli apsaugos sprendimai:
 - 5s užlaikymas po auksčio pasikeitimo. Kad nesaugotu kelis kartus, vykdant auksčio pasikeitimą.
 - kas 10`000 EEPROM ciklų, panaudojamas sekantis kitas atminties blokas.

### Tobulintinos vietos:
Padaryti saugojimą į EEPROM, tik dingus elektrai. Tam reikia su kondensatorių pagalba užtikrinti  su darbinę įtampą bent 100ms trukmei.
Įrašymui į EEPROM užtenka ~20ms. Atitinkamai, reikia implementuoti įtampos kritimo detektavimą per GPIO.

Dar galima būtu patobulinti kalibravimo mygtukų TOP/DOWN jautrumą. Įvertinant paspaudimo trukmę ir t.t.

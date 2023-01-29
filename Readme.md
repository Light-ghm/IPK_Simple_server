# Jednoduchý http server v jazyku C

### Autor: Marián Backa (xbacka01)

### Použitie

Aplikácia umožňuje užívateľovi získať základné informácie o zariadení, na ktorom beží, medzi ktoré patria:
* získanie doménového mena
* získanie informácí o CPU
* aktuálna záťaž servera

### Spustenie


```
  Stiahnite a extrahujte zazipovanú aplikáciu
  presunieme sa s konzolou do adresára aplikácie a preložíme ju nasledujúcim príkazom
$ make
  nasledujúcim príkazom spustíme aplikáciu kde <číslo portu> nahraďte za číslo portu s ktorým chcete aby aplikácia pracovala
$ ./hinfosvc <číslo portu>
```


### Ukážkové príklady použitia na vlastnom zariadení

 <číslo portu> to isté ktoré ste zadali do argumentu pri spúšťaní aplikácie

 V prehliadači:

```
http://localhost:<číslo portu>/hostname
http://localhost:<číslo portu>/cpu-name
http://localhost:<číslo portu>/load
```
 V konzoli:
```
$ curl http://localhost:<číslo portu>/hostname
$ curl http://localhost:<číslo portu>/cpu-name
$ curl http://localhost:<číslo portu>/load
```


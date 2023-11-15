1. 
- Localization affects the user interface of your application. Localization is controlled
by a neutral (language only) or specific (language and region) culture. You provide
multiple language versions of text and other values. For example, the label of a textbox
might be “First name” in English, and “Prénom” in French.
- Globalization affects the data of your application. Globalization is controlled by a spe-
cific (language and region) culture, for example, en-GB for British English, or fr-CA for
Canadian French. The culture must be specific because a decimal value formatted as
a currency must know to use Canadian dollars instead of French euros.
- Internationalization is the combination of localization and globalization.
2. Nanosecond.
3. 100 nanoseconds.
4. When exact time point is unimportant and might mess calculations.(especially for database mapping)
5. The differences between your time zone and UTC.
6. `TimeZoneInfo.Local`
7. Whether it's local or UTC.(or Unspecified)
8. Set `CultureInfo.CurrentCulture`/`CultureInfo.CurrentUICulture`
9. cy-GB
10. It tries to match both region and language first, then falls back to language only, finally falls back to default.

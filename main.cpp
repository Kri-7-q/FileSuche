#include <QTextStream>
#include <QDir>
#include <QFileInfo>
#include <QList>
#include <QString>
#include <QLocale>


void listDirectory(const QDir &dir, QTextStream &out, int deep);
unsigned abweichungLokaleZuSystem(const QString &locale, const QString &system);


int main(int argc, char *argv[])
{
    QTextStream out(stdout);
//    QDir dir(QString("/Users/Christian/link"));
//    if (dir.exists());
//    {
//        out << "Verzeichnisinhalt:\n-----------------------------------\n";
//        listDirectory(dir, out, 0);
//    }

    QLocale s = QLocale::system();
    out << "Punkte Liste:\n---------------------------------------\n";
    out << s.name() << "\n---------------------------------------\n";
    QString system("de_DE.UTF-8");
    QStringList list = { "de", "de_DE", "de_AT", "de_DE@euro", "en_US", "en_GB@euro", "de_DE.UTF-8" };
    for (const QString &lokale : list)
    {
        out << abweichungLokaleZuSystem(lokale, system) << endl;;
    }

    return 0;
}

void listDirectory(const QDir &dir, QTextStream &out, int deep)
{
    QString space(deep, ' ');
    QList<QFileInfo> infoList = dir.entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::Files);
    for (const QFileInfo &fi : infoList)
    {
        if (fi.isDir())
        {
            QDir d(fi.absoluteFilePath());
            listDirectory(d, out, deep+1);
        }
        else
            out << space << fi.fileName() << endl;
    }
}

// de,      de_DE,      de_DE.UTF-8,        de_DE@euro
unsigned abweichungLokaleZuSystem(const QString &locale, const QString &system)
{
    unsigned punkte = 5;
    int minLength = locale.length() < system.length() ? locale.length() : system.length();
    for (int index=0; index<minLength; ++index)
    {
        if (locale[index] != system[index])
        {
            if ( (locale[index] == '.' || locale[index] == '@') && (system[index] == '.' || system[index] == '@'))
                --punkte;
            return punkte;
        }
        if (locale[index] == '_' || locale[index] == '@' || locale[index] == '.')
            --punkte;
    }
    --punkte;

    return punkte;
}

#ifndef MUSICINFORMATION_H
#define MUSICINFORMATION_H

#include <QScopedPointer>

class MusicInformationPrivate;
class MusicInformation
{
    Q_DISABLE_COPY(MusicInformation)
public:
    MusicInformation();
    ~MusicInformation();
    void parserFilePath(const QString &path);
    QString getTitle();
    QString getArtist();
    QString getAlbum();
    QString getFileName();
private:
    friend class MusicInformationPrivate;
    QScopedPointer<MusicInformationPrivate> m_Private;
};

#endif // MUSICINFORMATION_H

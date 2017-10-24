#ifndef ID3TAGPARSER_H
#define ID3TAGPARSER_H

#include <QObject>
#include <QImage>
#include <QSharedPointer>

class ID3TagParserPrivate;
class ID3TagParser
{
    Q_DISABLE_COPY(ID3TagParser)
public:
    ID3TagParser();
    ~ID3TagParser();
    void parserFilePath(const QString &path);
    QString getFileName();
    QString getTitle();
    QString getArtist();
    QString getAlbum();
    int getEndTime();
    QImage getCover();
private:
    friend class ID3TagParserPrivate;
    QSharedPointer<ID3TagParserPrivate> m_Private;
};

#endif // ID3TAGPARSER_H

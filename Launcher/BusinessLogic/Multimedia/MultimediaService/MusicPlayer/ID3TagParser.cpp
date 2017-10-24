#include "ID3TagParser.h"
#include "attachedpictureframe.h"
#include "mpegfile.h"
#include "id3v2tag.h"
#include "fileref.h"
#include "tag.h"
#include "flacmetadatablock.h"
#include "flacfile.h"
#include <QFile>
#include <QPixmap>
#include <QDebug>
#include <QFileInfo>

class ID3TagParserPrivate
{
    Q_DISABLE_COPY(ID3TagParserPrivate)
public:
    ID3TagParserPrivate();
    ~ID3TagParserPrivate();
    void parsePixmap(const QString &path);
    void parseString(const QString &path);
    void parseInt(const TagLib::FileRef &fileRef);
    QString m_FileName;
    QString m_Title;
    QString m_Artist;
    QString m_Album;
    int m_EndTime;
    QImage m_Cover;

};

ID3TagParser::ID3TagParser()
    : m_Private(new ID3TagParserPrivate())
{
}

ID3TagParser::~ID3TagParser()
{
}

void ID3TagParser::parserFilePath(const QString &path)
{
    if (QFile::exists(path)) {
        m_Private->parseString(path);
        m_Private->parsePixmap(path);
    }
}

QString ID3TagParser::getFileName()
{
    return m_Private->m_FileName;
}

QString ID3TagParser::getTitle()
{
    return m_Private->m_Title;
}

QString ID3TagParser::getArtist()
{
    return m_Private->m_Artist;
}

QString ID3TagParser::getAlbum()
{
    return m_Private->m_Album;
}

int ID3TagParser::getEndTime()
{
    return m_Private->m_EndTime;
}

QImage ID3TagParser::getCover()
{
    return m_Private->m_Cover;
}

ID3TagParserPrivate::ID3TagParserPrivate()
{
    m_FileName.clear();
    m_Title.clear();
    m_Artist.clear();
    m_Album.clear();
    m_EndTime = 0;
}

ID3TagParserPrivate::~ID3TagParserPrivate()
{
}

void ID3TagParserPrivate::parsePixmap(const QString &path)
{
    QFileInfo fileInfo(path);
    if (fileInfo.suffix().contains(QString("mp3"), Qt::CaseInsensitive)) {
        TagLib::MPEG::File file(path.toLocal8Bit().constData());
        if ((file.hasID3v2Tag())
                && (NULL != file.ID3v2Tag())){
            TagLib::ID3v2::FrameList list = file.ID3v2Tag()->frameListMap()["APIC"];
            if (!list.isEmpty()) {
                TagLib::ID3v2::AttachedPictureFrame *picture = static_cast<TagLib::ID3v2::AttachedPictureFrame *>(list.front());
                if (NULL != picture) {
                    m_Cover.loadFromData((const unsigned char*)picture->picture().data(), picture->picture().size());
                    return ;
                }
            }
        }
    }
    m_Cover.loadFromData(NULL, 0);
}

void ID3TagParserPrivate::parseString(const QString &path)
{
    m_Title.clear();
    m_Artist.clear();
    m_Album.clear();
    m_EndTime = 0;
    QFileInfo fileInfo(path);
    m_FileName = fileInfo.fileName();
    TagLib::FileRef fileRef(path.toLocal8Bit().constData());
    if (fileInfo.suffix().contains(QString("mp3"), Qt::CaseInsensitive)) {
        if ((!fileRef.isNull())
                && (NULL != fileRef.tag())) {
            TagLib::Tag* tag = fileRef.tag();
#ifndef gcc
            m_Title = QString::fromStdWString(tag->title().toWString());
            m_Artist = QString::fromStdWString(tag->artist().toWString());
            m_Album = QString::fromStdWString(tag->album().toWString());
#endif
        }
    }
    parseInt(fileRef);
}

void ID3TagParserPrivate::parseInt(const TagLib::FileRef &fileRef)
{
    if ((!fileRef.isNull())
            && (NULL != fileRef.audioProperties())) {
        TagLib::AudioProperties *properties = fileRef.audioProperties();
        m_EndTime = properties->length();
    } else {
        m_EndTime = 0;
    }
}

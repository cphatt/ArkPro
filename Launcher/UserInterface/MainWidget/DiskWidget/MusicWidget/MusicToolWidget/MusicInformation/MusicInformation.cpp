#include "MusicInformation.h"
#include "attachedpictureframe.h"
#include "mpegfile.h"
#include "id3v2tag.h"
#include "fileref.h"
#include "tag.h"
#include "flacmetadatablock.h"
#include "flacfile.h"
#include "tstring.h"
#include "mp4file.h"
#include "mp4item.h"
#include "mp4coverart.h"
#include "mp4tag.h"
#include "apefile.h"
#include "apetag.h"
#include "apeitem.h"
#include "oggfile.h"
#include "vorbisfile.h"
#include "xiphcomment.h"
#include "QtConvert.h"
#include <QFile>
#include <QFileInfo>
#include <QDebug>

class MusicInformationPrivate
{
    Q_DISABLE_COPY(MusicInformationPrivate)
public:
    MusicInformationPrivate();
    ~MusicInformationPrivate();
    void parseString(const QString &path);
    QString m_Title;
    QString m_Artist;
    QString m_Album;
    QString m_FileName;
};

MusicInformation::MusicInformation()
    : m_Private(new MusicInformationPrivate())
{
}

MusicInformation::~MusicInformation()
{
}

void MusicInformation::parserFilePath(const QString &path)
{

    m_Private->parseString(path);


}

QString MusicInformation::getTitle()
{
    return m_Private->m_Title;
}

QString MusicInformation::getArtist()
{
    return m_Private->m_Artist;
}

QString MusicInformation::getAlbum()
{
    return m_Private->m_Album;
}
QString MusicInformation::getFileName()
{
    return m_Private->m_FileName;
}

MusicInformationPrivate::MusicInformationPrivate()
{
    m_Title.clear();
    m_Artist.clear();
    m_Album.clear();
}

MusicInformationPrivate::~MusicInformationPrivate()
{
}

void MusicInformationPrivate::parseString(const QString &path)
{
    m_Title.clear();
    m_Artist.clear();
    m_Album.clear();
    QFileInfo fileInfo(path);
    m_FileName = fileInfo.fileName();
    if (fileInfo.suffix().contains(QString("mp3"), Qt::CaseInsensitive)
            || (fileInfo.suffix().contains(QString("mp2"), Qt::CaseInsensitive))) {
//        TagLib::MPEG::File fileRef(path.toLocal8Bit().constData());
        TagLib::FileRef fileRef(path.toLocal8Bit().data());
        if ((!fileRef.isNull())
                && (NULL != fileRef.tag())) {
            TagLib::Tag* tag = fileRef.tag();
            m_Title = codecConvert(tag->title());
            m_Artist = codecConvert(tag->artist());
            m_Album = codecConvert(tag->album());
        }
//        if (NULL != fileRef.ID3v2Tag()) {
//            TagLib::ID3v2::Tag* tag = fileRef.ID3v2Tag();
//            m_Title = codecConvert(tag->title());
//            m_Artist = codecConvert(tag->artist());
//            m_Album = codecConvert(tag->album());
//        } else if (NULL != fileRef.ID3v1Tag()) {
//            TagLib::ID3v1::Tag* tag = fileRef.ID3v1Tag();
//            m_Title = codecConvert(tag->title());
//            m_Artist = codecConvert(tag->artist());
//            m_Album = codecConvert(tag->album());
//        } else if (NULL != fileRef.APETag()) {
//            TagLib::APE::Tag* tag = fileRef.APETag();
//            m_Title = codecConvert(tag->title());
//            m_Artist = codecConvert(tag->artist());
//            m_Album = codecConvert(tag->album());
//        }
    } else if (fileInfo.suffix().contains(QString("aac"), Qt::CaseInsensitive)
               || fileInfo.suffix().contains(QString("m4a"), Qt::CaseInsensitive)) {
        TagLib::MP4::File fileRef(path.toLocal8Bit().constData());
        if (NULL != fileRef.tag()) {
            TagLib::Tag* tag = fileRef.tag();
            m_Title = codecConvert(tag->title());
            m_Artist = codecConvert(tag->artist());
            m_Album = codecConvert(tag->album());
        }
    } else if (fileInfo.suffix().contains(QString("flac"), Qt::CaseInsensitive)) {
        TagLib::FLAC::File fileRef(path.toLocal8Bit().constData());
        if (NULL != fileRef.tag()) {
           TagLib::Tag* tag = fileRef.tag();
           m_Title = codecConvert(tag->title());
           m_Artist = codecConvert(tag->artist());
           m_Album = codecConvert(tag->album());
        }
    } else if (fileInfo.suffix().contains(QString("ape"), Qt::CaseInsensitive)) {
        TagLib::APE::File fileRef(path.toLocal8Bit().constData());
        if (NULL != fileRef.APETag()) {
            TagLib::APE::Tag* tag = fileRef.APETag();
            m_Title = codecConvert(tag->title());
            m_Artist = codecConvert(tag->artist());
            m_Album = codecConvert(tag->album());
        }
    } else if (fileInfo.suffix().contains(QString("ogg"), Qt::CaseInsensitive)) {
        TagLib::Ogg::Vorbis::File fileRef(path.toLocal8Bit().constData());
        if (NULL != fileRef.tag()) {
            TagLib::Ogg::XiphComment* tag = fileRef.tag();
            m_Title = codecConvert(tag->title());
            m_Artist = codecConvert(tag->artist());
            m_Album = codecConvert(tag->album());
        }
    }
}

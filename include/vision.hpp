// vision.hpp

#ifndef VISION_HPP
#define VISION_HPP

#include <QAbstractVideoBuffer>
#include <QAtomicInteger>
#include <QCamera>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QMediaObject>
#include <QMediaPlayer>
#include <QMutex>
#include <QStatusBar>

#include "acquisition.hpp"
#include "augmentation_widget.hpp"
#include "movement3d.hpp"
#include "movement3d_filter.hpp"

class vision : public QObject {
    Q_OBJECT

    public:
    vision (QStatusBar& statusbar, augmentation_widget& augmentation, QObject* parent);

    int max_debug_level ();
    void set_debug_level (const int level);
    int debug_level ();
    void set_input (const QCameraInfo& cameraInfo);
    void set_input (const QString& resource_path);
    void set_paused (bool paused);
    void set_focus ();
    void set_reference ();

    public slots:
    int get_and_clear_failed_frame_count ();
    void frame_callback (const QVideoFrame& const_buffer);
    void video_player_status_changed (QMediaPlayer::MediaStatus new_status);

    private:
    void execute_processing (image_t image);

    const int _max_debug_level = 3;

    points_t _markers;
    points_t _reference;
    movement3d_average _movement3d_average;
    QAtomicInteger<int> _failed_frames_counter;
    int _debug_level;
    augmentation_widget& _augmentation;
    QCamera* _cam;
    QMediaPlayer* _video_player;
    acquisition _acquisition;
    operators _operators;
    QStatusBar& _statusbar;
    QMutex _markers_mutex;
    QMutex _vision_mutex;
};

#endif // VISION_HPP

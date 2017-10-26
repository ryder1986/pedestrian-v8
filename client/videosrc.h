#ifndef VIDEOSRC_H
#define VIDEOSRC_H
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/ml/ml.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <QObject>
#include <QThread>
#include <QTimer>
#include <QMutex>
#include "common.h"
using namespace cv;
using namespace std;
class  VideoSrc:public QObject{
    Q_OBJECT
public:
    bool video_connected_flag;
    VideoSrc(QString path)
    {
        running=false;
        wait_duration=300;//waiting 200ms  before restart video src
        tick=0;
        video_connected_flag=true;
        memset(url,0,PATH_LEN);
        strcpy(url,path.toStdString().data());
        p_cap= cvCreateFileCapture(url);  //读取视频
        if(p_cap==NULL){
            prt(info,"video src start  %s err  ",url);
            video_connected_flag=false;
        }
        else
        { prt(info,"video src  start %s ok  ",url)}
        //        if(p_cap==NULL)
        //            emit video_disconnected();
        //        else
        //            emit video_connected();
        timer=new QTimer();
        //  tmr->singleShot(1000,this,SLOT(time_up()));

        //    prt(info," shot afer 100 ms")
        // QTimer::singleShot(1000,this,SLOT(time_up()));
        connect(timer,SIGNAL(timeout()),this,SLOT(time_up()));
        timer->start(wait_duration);
    }
    ~VideoSrc()
    {
        //   cap_lock.lock();
        timer->stop();

        disconnect(timer,SIGNAL(timeout()),this,SLOT(time_up()));
        delete timer;
        //     QThread::sleep(1);
        //   prt(info," delete src");



        //    disconnect(tmr,SIGNAL(timeout()),this,SLOT(time_up()));
        cvReleaseCapture(&p_cap);
        p_cap=NULL;
        //    cap_lock.unlock();
        //   delete tmr;
        //   delete p_cap;
    }
    Mat *get_frame()
    {

        //   cap_lock.lock();
        tick++;
        //prt(info,"fetchingframe %d",tick);
        //     tmr->singleShot(10,this,SLOT(time_up()));
        int err=0;
        if(p_cap==NULL){
            video_connected_flag=false;
            err=1;
            //   emit video_disconnected();
        }
        IplImage *ret_img;

        //            prt(info,"try to grb");
        //        int tmp= cvGrabFrame(p_cap);
        //             prt(info,"grub source url:%s ret %d (%p)",url,tmp,p_cap);
        //        ret_img= cvRetrieveFrame(p_cap);
        //   prt(info,"try to query");
        //    CV_CAP_PROP_XI_TIMEOUT
        //    int ret=cvSetCaptureProperty(p_cap,CV_CAP_PROP_XI_TIMEOUT,999);
        // double pro=cvGetCaptureProperty(p_cap,CV_CAP_PROP_XI_TIMEOUT);
        //  prt(info," set %d ,opecv time out %d",ret ,pro);
        //      CV_CAP_PROP_XI_TIMEOUT
        //prt(info,"  start query 1 frame ");
        ret_img=cvQueryFrame(p_cap);
        // prt(info,"  query 1 frame done");
        Mat *ret_mat=new Mat(ret_img,0);
        if(ret_img==NULL){
            //     prt(info,"get video source fail, source url:%s",url);
            err=1;
            //     std::this_thread::sleep_for(chrono::milliseconds(1000));
            //    QThread::sleep(1);
            if(video_connected_flag==true)
            {
                prt(info,"%s disconnected",url);
                video_connected_flag=false;

            }
            //    emit video_disconnected();
            //     prt(info,"sleep done");
        }else{
            running=true;
            //    prt(info,"%s runing",url);
            if(video_connected_flag==false)
            {
                prt(info,"%s connected",url);
                video_connected_flag=true;
                //        emit video_connected();
            }
            //    prt(info,"get video source url:  size %d",ret_img->imageSize);
        }
        //   cap_lock.unlock();
        if(err)
            return NULL;
        else
            return ret_mat;
    }
    char *get_url(){
        return url;
    }
public slots:
    void time_up()
    {

        //prt(info,"@@@@@@@@@@@@@@@@@@@@@ checking per %d seconds",wait_duration/1000);
        if(running == false)
        {
            //    prt(info,"################## source need restart ");
            //  emit video_disconnected();
        }
        running= false;
        //     QTimer::singleShot(wait_duration,this,SLOT(time_up()));
    }

signals:
    //    void video_connected();
    void video_disconnected();

private:
    bool running;
    int wait_duration;
    int tick;
    QTimer *timer;
    CvCapture *p_cap;
    char url[PATH_LEN];
    //  QMutex cap_lock;
};

#endif // VIDEOSRC_H

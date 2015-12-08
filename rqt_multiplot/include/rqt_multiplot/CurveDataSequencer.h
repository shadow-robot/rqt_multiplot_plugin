/******************************************************************************
 * Copyright (C) 2015 by Ralf Kaestner                                        *
 * ralf.kaestner@gmail.com                                                    *
 *                                                                            *
 * This program is free software; you can redistribute it and/or modify       *
 * it under the terms of the Lesser GNU General Public License as published by*
 * the Free Software Foundation; either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the               *
 * Lesser GNU General Public License for more details.                        *
 *                                                                            *
 * You should have received a copy of the Lesser GNU General Public License   *
 * along with this program. If not, see <http://www.gnu.org/licenses/>.       *
 ******************************************************************************/

#ifndef RQT_MULTIPLOT_CURVE_DATA_SEQUENCER_H
#define RQT_MULTIPLOT_CURVE_DATA_SEQUENCER_H

#include <QObject>
#include <QPointF>
#include <QVector>

#include <rqt_multiplot/CurveConfig.h>
#include <rqt_multiplot/MessageSubscriberRegistry.h>

namespace rqt_multiplot {
  class CurveDataSequencer :
    public QObject {
  Q_OBJECT
  public:
    CurveDataSequencer(QObject* parent = 0);
    virtual ~CurveDataSequencer();
    
    void setConfig(CurveConfig* config);
    CurveConfig* getConfig() const;
    bool isSubscribed() const;
    
    void subscribe();
    void unsubscribe();
    
  signals:
    void subscribed();
    void pointReceived(const QPointF& point);
    void unsubscribed();
    
  private:
    CurveConfig* config_;
    
    MessageSubscriberRegistry* registry_;
    QVector<MessageSubscriber*> subscribers_;
    
  private slots:
    void configAxisConfigChanged();
    void configSubscriberQueueSizeChanged(size_t queueSize);
    
    void subscriberMessageReceived(const QString& topic, const Message&
      message);
  };
};

#endif

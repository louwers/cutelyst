/*
 * Copyright (C) 2013 Daniel Nicoletti <dantti12@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; see the file COPYING.LIB. If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301, USA.
 */

#ifndef CUTELYSTDISPATCHTYPE_H
#define CUTELYSTDISPATCHTYPE_H

#include <QObject>

class CutelystAction;
class CutelystContext;
class CutelystDispatchType : public QObject
{
    Q_OBJECT
public:
    explicit CutelystDispatchType(QObject *parent = 0);

    /**
     * @brief list the registered actions
     * To be implemented by subclasses
     */
    virtual void list() const = 0;

    /**
     * Return true if the dispatchType matches the given path
     */
    virtual bool match(CutelystContext *c, const QString &path) const = 0;

    /**
     * @brief registerAction
     * @param action
     * @return
     */
    virtual bool registerAction(CutelystAction *action) = 0;

    /**
     * Returns true if the dispatch type has low precedence
     * when the precedence is the same the Class name is used
     * to sort them.
     */
    virtual bool isLowPrecedence() const;

protected:
    void setupMatchedAction(CutelystContext *c, CutelystAction *action, const QString &match) const;
};

#endif // CUTELYSTDISPATCHTYPE_H
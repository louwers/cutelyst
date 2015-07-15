/*
 * Copyright (C) 2013-2015 Daniel Nicoletti <dantti12@gmail.com>
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

#ifndef CUTELYST_CONTROLLER_H
#define CUTELYST_CONTROLLER_H

#include <QObject>

#include <Cutelyst/Action>
#include <Cutelyst/Context>
#include <Cutelyst/Request>
#include <Cutelyst/Response>

#define STR(X) #X
#define C_PATH(X, Y) Q_CLASSINFO(STR(X ## _Path), STR(Y))
#define C_NAMESPACE(value) Q_CLASSINFO("Namespace", value)
#define C_ATTR(X, Y) Q_CLASSINFO(STR(X), STR(Y)) Q_INVOKABLE

namespace  Cutelyst {

class ControllerPrivate;
/**
 * \class Controller
 *
 * Use C_ATTR to give hints about methods
 * build like methodName_option
 * Where option is one of the following:
 *
 * \b :Path - An ending path relative to the class info Namespace
 * for example:
 * \n :Path("") - /namespace/controlername (used for the index)
 * \n :Path("foo") - /namespace/controlername/foo
 * \n :Path("/bar") - /namespace/bar
 *
 * \b :Chained - Sets the name of this part of the chain. If it
 * is specified without arguments, it takes the name of
 * the action as default.
 *
 * \b :PathPart - The part of the chained path
 *
 * \b :Args - In the case of more than 9 parameters, to build
 * the path set the needed number here, where an empty string
 * means unlimited arguments.
 *
 * \b :CaptureArgs - In the case of more than 9 parameters, to
 * be captured the path set the needed number here, where -1
 * means unlimited arguments.
 *
 * \b :Global - Alias to Path="/methodname" which sets the
 * method relative to your root.
 *
 * \b :Local - Alias to Path="methodname".
 *
 * \b :Args - When used with "Path" it indicates the number of
 * arguments in the path.
 * \n The number is computed by counting the arguments the method expects.
 * \n However if no Args value is set, assumed to 'slurp' all
 *    remaining path parts under this namespace.
 */
class Controller : public QObject
{
    Q_OBJECT
public:
    explicit Controller(Application *app);
    virtual ~Controller();

    /**
     * This specifies the internal namespace the controller should
     * be bound to.
     * By default the controller is bound to the URI version of the
     * controller name. For instance a controller named
     * 'MyFooBar' will be bound to 'my/foo/bar'.
     * The default Root controller is an example of setting
     * namespace to '' (the null string).
     */
    QString ns() const;

    /**
     * Returns the Cutelyst::Action object (if any) for a given method name in
     * this class namespace.
     */
    Action *actionFor(const QString &name) const;

    /**
     * Returns the Cutelyst::ActionList containing all actions which belongs to
     * this controller.
     */
    ActionList actions() const;

    /**
     * Return TRUE if className is equal to this Controller's name
     */
    bool operator==(const char *className);

protected:
    virtual void Begin(Context *c);
    virtual bool Auto(Context *c);
    virtual void End(Context *c);

    /**
     * This method is called after the application
     * has registered all controllers.
     *
     * Reimplement this method if you need to configure
     * internal variable and you need to know for
     * example which configuration options are enabled.
     */
    virtual bool preFork(Application *app);

    /**
     * This method is called after the application
     * has registered all controllers.
     *
     * Reimplement this method if you need to configure
     * internal variable and you need to know for
     * example which configuration options are enabled.
     */
    virtual bool postFork(Application *app);

    ControllerPrivate *d_ptr;

private Q_SLOTS:
    bool _DISPATCH(Context *c);
    bool _BEGIN(Context *c);
    bool _AUTO(Context *c);
    bool _ACTION(Context *c);
    bool _END(Context *c);

private:
    Q_DECLARE_PRIVATE(Controller)
    friend class Action;
    friend class Application;
    friend class Dispatcher;
};

}

#endif // CUTELYST_CONTROLLER_H

#ifndef SINGLEAPPLICATION_H
#define SINGLEAPPLICATION_H

#include <string>

void singleApplication(const std::string &key);

typedef void (*HANDLER) (void*);
HANDLER acquirePreemptiveResource(HANDLER callback, void *parameter);
void clearOwner();

#endif // SINGLEAPPLICATION_H

//
// Created by parallels on 9/26/16.
//

#include "query.pb.h"

#include <iostream>
#include <typeinfo>
#include <string>
#include <google/protobuf/descriptor.h>

typedef dio::Query T;

using namespace std;
using namespace ::google::protobuf;

int main() {
    string descript_name = T::descriptor()->full_name();
    cout << "descript_name: " << descript_name << endl;

    const Descriptor* descriptor = DescriptorPool::generated_pool()->FindMessageTypeByName(descript_name);
    assert(descriptor == T::descriptor());

    const Message* prototype = MessageFactory::generated_factory()->GetPrototype(descriptor);
    assert(prototype == &T::default_instance());

    T *newObj = dynamic_cast<T*>(prototype->New());
    assert(newObj != NULL);
    assert(newObj != prototype);

    assert(typeid(*newObj) == typeid(T::default_instance()));
    delete newObj;
    return 0;
}

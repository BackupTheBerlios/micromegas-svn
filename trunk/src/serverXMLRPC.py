#!/usr/bin/env python

from SocketServer import *
from SimpleXMLRPCServer import *
from calcul import *

# Serveur XML-RPC
class ArfXMLRPCServer (SimpleXMLRPCServer, ThreadingMixIn):
    def __init__(self):
        SimpleXMLRPCServer.__init__(self, ('127.0.0.1', 1981))

# Fonction principale
def main():
    srv = ArfXMLRPCServer()
    srv.register_function(initArbo)
    srv.register_function(specialiser)
    srv.register_function(sauter)
    srv.serve_forever()

if __name__ == '__main__':
    main()
    
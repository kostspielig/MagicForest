

#ifndef MGE_TREE_H
#define MGE_TREE_H

#include <iostream>
#include <map>
#include "mapiterator.h"

namespace mge
{

  template <class KeyType, class NodeType> 
  class TreeNode
  {
    std::map<KeyType, NodeType*> m_childs;
    NodeType* m_parent;
    KeyType m_name;
    bool m_isinit;

    virtual void onNewChild(NodeType& node) {}
    virtual void onRemoveChild(NodeType& node) {}
    virtual void onInit() {}
    virtual void onUnInit() {}
    
    /**
     * Returns Si el nodo ha sido inicializado.
     */
    bool isInit() const {
      return m_isinit;
    }

    /**
     * Inicializa estableciendo en nombre y el padre del nodo configurado
     * @param name El nombre del nodo configurado.
     * @param parent El padre de este nodo configurado.
     */
    void init(const KeyType& name, NodeType* parent) {
      if (!m_isinit) {
	m_isinit = true;
	m_name = name;
	m_parent = parent;
	onInit();
      }
    }

    /**
     * No-Inicializa el nodo.
     */
    void unInit() {
      if (m_isinit) {
	m_isinit = false;
	m_name = KeyType();
	m_parent = 0;
	onUnInit();
      }
    }
    
  public:
    /**
     * Iterator Comprueba los hijos de este nodo.
     */
    typedef MapIterator<KeyType, NodeType*> ChildIter;

    /**
     * Iterator Comprueba los hijos de este nodo, versión constante.
     */
    typedef MapConstIterator<KeyType, NodeType*> ConstChildIter;

    
    /** Constuctor. */
    TreeNode() :
      m_parent(0),
      m_isinit(false)
    {};

    /** Destructor */
    ~TreeNode() {
      unInit();
      ChildIter iter = begin();
      while(iter != end())
	delete *iter++;
    }

    /**
     * Returns un iterador con el primer hijo de este nodo.
     */
    ChildIter begin() {
      return m_childs.begin();
    }

    /**
     * Returns un iterador con el primer hijo de este nodo. Versión constante.
     */
    ConstChildIter begin() const {
      return m_childs.begin();
    }

    /**
     * Returns un iterador al final de este nodo hijo.
     */
    ChildIter end() {
      return m_childs.end();
    }

    /**
     * Returns  un iterador al final de este nodo hijo. Versión constante.
     */
      ConstChildIter end() const {
      return m_childs.end();
    }

    /** 
     * Encuentra un hijo devuelve un iterador a éste.
     */
    ChildIter find(const KeyType& key) {
      return m_childs.find (key);
    }

    /**
     *  Encuentra un hijo devuelve un iterador constante a éste.
     */

    ConstChildIter find (const KeyType& key) const {
      return m_childs.find (key);
    }
    
    /**
     * Devuelve una referencia al hijo de este nodo con el que concuerde el nombre.
     *  El hijo es creado en caso de que no exista.
     * @param name El nombre del hijo.
     */
    NodeType& getChild(const KeyType& name) {
      if (!m_childs[name]) {
	m_childs[name] = new NodeType();
	m_childs[name]->init(name, (NodeType*)(this));
	onNewChild(*m_childs[name]);
      }
	
      return *m_childs[name];
    }
  
    /**
     * Borra un hijo de este nodo.
     * @return Un iterador al siguente hijo.
     */
    ChildIter removeChild(ChildIter& iter) {
      ChildIter next = iter;
      next++;
      onRemoveChild(**iter);
      (*iter)->uninit();
      delete *iter;
      m_childs.erase(iter);
      return next;
    }

    /**
     * Borra un jijo de ese nodo.
     * @return false si no existian hijos con el nombre o es true
     * para éxito.
     */
    void removeChild (KeyType& key) {
      ChildIter child = find (key);
      if (child != end()) {
	removeChild (child);
	return true;
      }
      return false;
    }
    
    /**
     * Borra todos los hijos.
     */
    void clearChilds() {
      ChildIter iter = begin();
      while(iter != end())
	iter = removeChild(iter);
    }
    
    /**
     * Devuelve un puntero constante al padre de este nodo o null si es el
     * nodo raíz.
     */
    const NodeType* getParent() const {
      return m_parent;
    }

    /**
     * Devuelve un puntero al padre de este nodo o null si es un nodo
     * raíz.
     */
    NodeType* getParent() {
      return m_parent;
    }
    
    /**
     * Devuelve el nombre de este nodo.
     */
    const KeyType& getName() const {
      return m_name;
    }
    
    /**
     * Devuelve la ruta de este nodo desde la raiz al nodo.
     */
    KeyType getPathName() const {
      if (m_parent)
	return m_parent->getPathName() + "/" + m_name;
      else
	return m_name;
    }

    /**
     * Devuelve una referencia al hijo que concuerda con el path. El path se
     * construye separando hijos consecutivos por / como los nombres de archivos.
     * Cualquier nodo del paht que no exista se crea.
     */
    NodeType& getPath(KeyType name);

    /**
     * Ata un nodo al árbole. Notar que un nodo no debe ser atado
     * a varios árboles. El árbol padre será el dueño del ciclo de
     * vida del nodo
     * @return true Si el nodo fue atado, false si este árbol ya tiene
     * un hijo con este nombre o si el nodo tiene un padre.
     */
    bool attach (KeyType name, NodeType* node) {
      if (node->m_isinit)
	return false;
      ChildIter iter = find(name);
      if (iter != end ())
	return false;

      node->init(name, (NodeType*)(this));
      m_childs.insert(std::make_pair(name, node));
      onNewChild(*node);
      return true;
    }

    /**
     * Quita un nodo de este árbolDetaches a node from this tree.
     * @return null si no habia ningún hijo con el nombre o un puntero
     * al nodo quitado.Un nodo quitado pierde su nombre.
     */
    NodeType* detach (const KeyType& name) {
      ChildIter it = find (name);
      if (it != end()) {
	return detach(it);
      }
      return 0;
    }

    /**
     * Borra un nodo del árbol.
     * @return A Puntero al nodo borrado.
     */
    NodeType* detach (ChildIter& iter) {
      NodeType* node = *iter;
      m_childs.erase(iter);
      onRemoveChild(**iter);
      node->unInit();
      return node;
    }
  };

  template<class KeyType, class NodeType>
  NodeType& TreeNode<KeyType, NodeType>::getPath(KeyType path)
  {
    std::string base;
    for (size_t i = 0; i != path.size(); ++i)
      if (path[i] == '/') {
	base.assign(path, 0, i);
	while(path[++i] == '/');
	path.erase(0, i);
	break;
      }

    if (base.empty()) {
      return getChild(path);
    }

    return getChild(base).getPath(path);
  }

} /* namespace mge */

#endif /* MGE_TREE_H  */

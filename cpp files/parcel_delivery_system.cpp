#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <set>
#include <queue>
#include <stack>
#include <list>
#include <bits/stdc++.h>

class Parcel
{
public:
    int time_tick;
    std::string parcel_id;
    std::string origin;
    std::string destination;
    int priority;
    bool delivered;
    std::string current_location;
    std::map<int, std::string> tick_location;
    int deliveredat;

    Parcel() = default;
    Parcel(int time_tick, std::string parcel_id, std::string origin, std::string destination, int priority)
    {
        this->time_tick = time_tick;
        this->parcel_id = parcel_id;
        this->origin = origin;
        this->destination = destination;
        this->priority = priority;
        this->delivered = false;
        this->current_location = origin;
        this->deliveredat = -1;
    }

    void updatetick(int tick)
    {
        tick_location[tick] = current_location;
        if (current_location == destination)
        {
            deliveredat = tick;
        }
    }
};

class MaxHeap
{
public:
    std::vector<Parcel *> heap;

    int parent(int i) { return (i - 1) / 2; }
    int left(int i) { return (2 * i) + 1; }
    int right(int i) { return (2 * i) + 2; }

    Parcel *get_max()
    {
        // fill in this function
        if (!heap.empty())
            return heap[0];
        else
            throw std::runtime_error("Heap of pointers is empty");
    }

    Parcel *extract_max()
    {
        if (heap.empty())
            throw std::runtime_error("Heap of pointers is empty");

        Parcel *root = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        if (!heap.empty())
            max_heapify(0);
        return root;
        // function that returns the max element and removes it from the heap
    }

    void max_heapify(int i)
    {
        int l = left(i);
        int r = right(i);
        int largest = i;

        if (l < heap.size() && heap[l]->priority > heap[i]->priority)
            largest = l;
        if (r < heap.size() && heap[r]->priority > heap[largest]->priority)
            largest = r;

        if (largest != i)
        {
            std::swap(heap[i], heap[largest]);
            max_heapify(largest);
        }
        // function that maintains the max heap property
    }

    void insert(Parcel *item)
    {
        // function that inserts item into the heap
        heap.push_back(item);
        int i = heap.size() - 1;

        while (i != 0 && heap[parent(i)]->priority < heap[i]->priority)
        {
            std::swap(heap[i], heap[parent(i)]);
            i = parent(i);
        }
    }

    bool is_empty()
    {
        return heap.empty();
    }
};

class FreightCar
{
public:
    int max_parcel_capacity;
    std::vector<Parcel *> parcels;
    std::string destination_city;
    std::string next_link;
    std::string current_location;
    bool sealed;
    std::vector<std::string> visited_vertices;
    bool reached;

    FreightCar(int max_parcel_capacity)
    {
        this->max_parcel_capacity = max_parcel_capacity;
        // instantiate parcels vector as empty initially
        this->parcels = {};
        this->destination_city = "";
        this->next_link = "";
        this->current_location = "";
        this->sealed = false;
        this->reached = false;
    }

    void load_parcel(Parcel *parcel)
    {
        // load parcel
        // Check if there's capacity to load the parcel
        if (parcels.size() < max_parcel_capacity)
        {
            parcels.push_back(parcel);
            // If this is the first parcel, set the destination city
            if (parcels.size() == 1)
            {
                destination_city = parcel->destination;
                visited_vertices.push_back(current_location);
            }
            // If the freight car is full, seal it
            // if (parcels.size() == max_parcel_capacity) {
            //  sealed = true;
            // Compute the next link (BFS or DFS) - placeholder for actual implementation
            // compute_next_link();=====
            // }
        }
        else
        {
            // Handle the case when the freight car is full - maybe throw an exception or log a message
            std::cout << "Attempted to load a parcel into a full freight car." << std::endl;
        }
    }

    bool can_move()
    {
        return (parcels.size() == max_parcel_capacity && reached != true);
        // if length of parcels is equal to max_parcel_capacity return true else return false
    }

    void move(std::string destination)
    {
        // function that moves freight car to destination (link)
        // Update the current location to the destination
        // This is a simplification, the actual move will involve graph traversal
        current_location = destination;
        visited_vertices.push_back(current_location);
        sealed = true;
        if (destination_city == destination)
        {
            reached = true;
        }
        for (auto i : parcels)
        {
            i->current_location = destination;
            if (i->current_location == i->destination)
            {
                i->delivered = true;
            }
        }
        // Once the freight car has moved, you may need to recompute the next link
        // For now, we clear it to indicate it needs to be recomputed
        next_link.clear();
    }
};

class Vertex
{
    // public:
    //     std::string name;
    //     std::vector<FreightCar *> freight_cars;
    //     std::vector<Vertex *> neighbors;
    //     // trains_to_move is dict of destination and freight cars
    //     std::map<std::string, std::vector<FreightCar *>> trains_to_move;
    //     int min_freight_cars_to_move;
    //     int max_parcel_capacity;
    //     std::unordered_map<std::string, MaxHeap> parcel_destination_heaps;
    //     std::vector<FreightCar *> sealed_freight_cars;
    //     std::vector<Parcel *> all_parcels;
    //     Vertex() = default;
    //     Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity)
    //     {
    //         this->name = name;
    //         this->freight_cars = {};
    //         this->neighbors = {};
    //         this->trains_to_move = {};
    //         this->min_freight_cars_to_move = min_freight_cars_to_move;
    //         this->max_parcel_capacity = max_parcel_capacity;
    //         this->parcel_destination_heaps = {};
    //         this->sealed_freight_cars = {};
    //         this->all_parcels = {};
    //     }

    //     void add_neighbor(Vertex *neighbor)
    //     {
    //         // add neighbor to neighbors vector
    //     }

    //     // add get neighbors function
    //     std::vector<Vertex *> get_neighbors()
    //     {
    //         return this->neighbors;
    //     }

public:
    std::string name;
    std::vector<FreightCar *> freight_cars;
    std::vector<Vertex *> neighbors;
    // trains_to_move is dict of destination and freight cars
    std::map<std::string, std::vector<FreightCar *>> trains_to_move;
    // std::map<std::string, std::vector<FreightCar>> trains_ptr;
    int min_freight_cars_to_move;
    int max_parcel_capacity;
    std::unordered_map<std::string, MaxHeap> parcel_destination_heaps;
    std::vector<FreightCar *> sealed_freight_cars;
    std::vector<Parcel *> all_parcels;
    Vertex() = default;
    Vertex(std::string name, int min_freight_cars_to_move, int max_parcel_capacity)
    {
        this->name = name;
        this->freight_cars = {};
        this->neighbors = {};
        this->trains_to_move = {};
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->max_parcel_capacity = max_parcel_capacity;
        this->parcel_destination_heaps = {};
        this->sealed_freight_cars = {};
        this->all_parcels = {};
    }

    void add_neighbor(Vertex *neighbor)
    {
        // add neighbor to neighbors vector
        if (std::find(neighbors.begin(), neighbors.end(), neighbor) == neighbors.end())
        {
            neighbors.push_back(neighbor);
        }
    }

    // add get neighbors function
    std::vector<Vertex *> get_neighbors()
    {
        return this->neighbors;
    }

    std::vector<Parcel *> get_all_current_parcels()
    {
        // get all parcels from all destination heaps
        // get all parcels from all destination heaps
        std::vector<Parcel *> all_current_parcels;
        for (auto &[destination, heap] : parcel_destination_heaps)
        {
            std::vector<Parcel *> &parcels = heap.heap;
            all_current_parcels.insert(all_current_parcels.end(), parcels.begin(), parcels.end());
        }
        return all_current_parcels;
    }

    void clean_unmoved_freight_cars()
    {
        auto it = freight_cars.begin();
        while (it != freight_cars.end())
        {
            // if (it->parcels.size() < max_parcel_capacity)
            //{
            //  Move parcels back to the heap before erasing the freight car
            for (Parcel *parcel : (*it)->parcels)
            {
                loadParcel(parcel);
                // loadParcelptr(parcel);
            }
            it = freight_cars.erase(it);
            //}
            // else
            //{
            //  ++it;
            //}
        }
        // after time tick t, freight cars with parcels < min parcels should be deleted and parcels are to be added to heap
    }

    void loadParcel(Parcel *parcel)
    {
        // load parcel into heap
        parcel_destination_heaps[parcel->destination].insert(parcel);
    }

    void loadFreightCars()
    {
        for (auto &[destination, heap] : parcel_destination_heaps)
        {
            while (!heap.is_empty() && heap.heap.size() >= max_parcel_capacity)
            {
                FreightCar *freight_car = new FreightCar(max_parcel_capacity);
                while (!heap.is_empty() && freight_car->parcels.size() < max_parcel_capacity)
                {
                    Parcel *parcel = heap.extract_max();
                    // Parcel parcl = heap.extract_max();
                    freight_car->load_parcel(parcel);
                }

                // if(freight_car.parcels.size()==max_parcel_capacity)
                // {
                //     sealed_freight_cars.push_back(freight_car);
                // }
                freight_cars.push_back(freight_car);
            }
        } // load parcels into freight cars (making sure that each freight car has parcels from only one destination, and # parcels == min_parcel_capacity)
    }

    void print_parcels_in_freight_cars()
    {
        for (auto &[destination, heap] : this->parcel_destination_heaps)
        {
            for (auto &parcel : heap.heap)
            {
                std::cout << "Parcel ID: " << parcel->parcel_id << ", Parcel origin: " << parcel->origin << ", Parcel destination: " << parcel->destination << ", Parcel priority: " << parcel->priority << std::endl;
            }
        }
    }
};

class Graph
{

public:
    std::list<Vertex *> vertices;
    std::vector<std::pair<Vertex *, Vertex *>> edges;

    void add_edge(std::string source, std::string destination, int min_freight_cars_to_move, int max_parcel_capacity)
    {

        // check if source and destination vertices exist
        // if they do not exist, create them
        // add edges accordingly

        Vertex *source_vertex = find_vertex(source);
        if (!source_vertex)
        {
            source_vertex = new Vertex(source, min_freight_cars_to_move, max_parcel_capacity);
            vertices.push_back(source_vertex);
        }

        Vertex *dest_vertex = find_vertex(destination);
        if (!dest_vertex)
        {
            dest_vertex = new Vertex(destination, min_freight_cars_to_move, max_parcel_capacity);
            vertices.push_back(dest_vertex);
        }

        source_vertex->add_neighbor(dest_vertex);
        dest_vertex->add_neighbor(source_vertex);
        edges.emplace_back(source_vertex, dest_vertex);
    }

    Vertex *find_vertex(const std::string &name)
    {
        for (Vertex *vertex : vertices)
        {
            if (vertex->name == name)
            {
                return vertex;
            }
        }
        return nullptr;
    }

    void print_graph()
    {
        std::cout << "Printing graph, vertices: " << vertices.size() << std::endl;
        for (auto &vertex : this->vertices)
        {
            std::cout << "Vertex: " << vertex->name << std::endl;
            std::cout << "Neighbors: ";
            for (auto &neighbor : vertex->neighbors)
            {
                std::cout << neighbor->name << " ";
            }
            std::cout << std::endl;
        }
    }

    bool contains_visited(std::vector<std::string> path, std::vector<std::string> visited)
    {
        for (auto i : visited)
        {
            if (find(path.begin(), path.end(), i) != path.end())
            {
                return true;
            }
        }

        return false;
    }

    std::vector<std::string> bfs(std::string source, std::string destination)
    {
        std::unordered_map<Vertex *, Vertex *> prev;
        std::queue<Vertex *> q;
        std::unordered_set<Vertex *> visited;

        Vertex *source_vertex = find_vertex(source);
        if (!source_vertex)
        {
            return {}; // Source vertex not found
        }

        q.push(source_vertex);
        visited.insert(source_vertex);
        prev[source_vertex] = nullptr; // source has no predecessor

        while (!q.empty())
        {
            Vertex *current = q.front();
            q.pop();

            if (current->name == destination)
            {
                std::vector<std::string> path;
                for (Vertex *at = current; at != nullptr; at = prev[at])
                {
                    path.push_back(at->name);
                }
                std::reverse(path.begin(), path.end());
                return path;
            }

            for (Vertex *neighbor : current->neighbors)
            {
                if (visited.find(neighbor) == visited.end())
                {
                    visited.insert(neighbor);
                    prev[neighbor] = current;
                    q.push(neighbor);
                }
            }
        }
        return {}; // return empty path if destination not found
    }

    /* void dfs_recursive(Vertex *current, Vertex *destination, std::unordered_set<std::string> &visited, std::vector<std::string> &path, std::vector<std::vector<std::string>> &paths)
     {
         path.push_back(current->name);
         visited.insert(current->name);

         if (current == destination)
         {
             paths.push_back(path);
         }
         else
         {
             for (Vertex *neighbor : current->neighbors)
             {
                 if (visited.find(neighbor->name) == visited.end())
                 {
                     dfs_recursive(neighbor, destination, visited, path, paths);
                 }
             }
         }

         path.pop_back();
         visited.erase(current->name);
     }

     std::vector<std::vector<std::string>> dfs(std::string source, std::string destination)
     {
         // function to return path from source to destination using dfs
         Vertex *source_vertex = nullptr;
         Vertex *destination_vertex = nullptr;

         // Find the source and destination vertices
         for (auto &vertex : vertices)
         {
             if (vertex.name == source)
                 source_vertex = &vertex;
             if (vertex.name == destination)
                 destination_vertex = &vertex;
         }

         std::vector<std::vector<std::string>> paths;
         if (source_vertex && destination_vertex)
         {
             std::vector<std::string> path;
             std::unordered_set<std::string> visited;
             dfs_recursive(source_vertex, destination_vertex, visited, path, paths);
         }

         return paths;
     }

     */
    bool dfs_recursive(Vertex *current, Vertex *destination, std::unordered_set<Vertex *> &visited, std::vector<std::string> &path, std::vector<std::vector<std::string>> &paths)
    {
        path.push_back(current->name);
        visited.insert(current);

        if (current == destination)
        {
            paths.push_back(path);
            return true; // Return true to indicate that the first path is found
        }
        else
        {
            for (Vertex *neighbor : current->neighbors)
            {
                if (visited.find(neighbor) == visited.end())
                {
                    if (dfs_recursive(neighbor, destination, visited, path, paths))
                    {
                        return true; // Return true if the first path is found
                    }
                }
            }
        }

        path.pop_back();
        visited.erase(current);

        return false; // Return false if no path is found so far
    }

    std::vector<std::string>dfs(std::string source, std::string destination)
    {
            std::vector<std::vector<std::string>> paths = dfshelp(source,destination);
            if(!paths.empty())
            {
            return paths[0];
    }

    else{
        return {};
    }
    }

    std::vector<std::vector<std::string>> dfshelp(std::string source, std::string destination)
    {
        Vertex *source_vertex = find_vertex(source);
        Vertex *destination_vertex = find_vertex(destination);
        std::vector<std::vector<std::string>> paths;

        if (source_vertex && destination_vertex)
        {
            std::vector<std::string> path;
            std::unordered_set<Vertex *> visited;
            dfs_recursive(source_vertex, destination_vertex, visited, path, paths);
        }

        return paths;
    }

    std::vector<std::string> find_dfs_path_no_repetition(std::string source, std::string destination,
                                                         std::vector<std::string> visited_vertices)
    {
        Vertex *source_vertex = find_vertex(source);
        Vertex *destination_vertex = find_vertex(destination);
        if (!source_vertex || !destination_vertex)
        {
            return {};
        }
        std::vector<std::string> path;
        std::unordered_set<std::string> visited;
        // Convert the vector to a set for efficient lookup
        std::unordered_set<std::string> excluded_vertices(visited_vertices.begin(), visited_vertices.end());

        if (dfs_no_repetition(source_vertex, destination_vertex, visited, path, excluded_vertices))
        {
            return path; // Return the first valid path found
        }
        else
        {
            return {}; // Return an empty path if no valid paths are found
        }
    }

    bool dfs_no_repetition(Vertex *current, Vertex *destination,
                           std::unordered_set<std::string> &visited,
                           std::vector<std::string> &path,
                           const std::unordered_set<std::string> &excluded_vertices)
    {
        path.push_back(current->name);
        visited.insert(current->name);

        if (current == destination)
        {
            return true; // Destination found, stop the search
        }
        else
        {
            for (Vertex *neighbor : current->neighbors)
            {
                if (visited.find(neighbor->name) == visited.end() &&
                    excluded_vertices.find(neighbor->name) == excluded_vertices.end())
                {
                    if (dfs_no_repetition(neighbor, destination, visited, path, excluded_vertices))
                    {
                        return true; // Valid path found, propagate success back up the recursion stack
                    }
                }
            }
        }

        path.pop_back();
        visited.erase(current->name);
        return false; // No valid path found from this vertex, backtrack
    }

    void groupFreightCars()
    {
        // for every vertex, group freight cars by links
        for (auto &vertex_ptr : vertices)
        {
            Vertex &vertex = *vertex_ptr;
            std::unordered_map<std::string, std::vector<FreightCar *>> link_groups_bfs;
            std::unordered_map<std::string, std::vector<FreightCar *>> link_groups_dfs;

            // Separate the movable cars for BFS grouping
            for (auto it = vertex.freight_cars.begin(); it != vertex.freight_cars.end();)
            {
                if ((*it)->parcels.size() == vertex.max_parcel_capacity && (*it)->can_move() == true)
                { // car is ready to move
                    std::vector<std::string> pathbfs = bfs(vertex_ptr->name, (*it)->destination_city);
                     if(pathbfs.empty())
                    {
                        ++it;
                        continue;
                    }
                    (*it)->next_link = pathbfs[1];

                    link_groups_bfs[(*it)->next_link].push_back(&(*(*it)));
                    it = vertex.freight_cars.erase(it); // Erase and advance the iterator
                }
                else
                {
                    ++it; // Only advance the iterator
                }
            }

            for (auto it = vertex.sealed_freight_cars.begin(); it != vertex.sealed_freight_cars.end();)
            {
                if ((*it)->parcels.size() == vertex.max_parcel_capacity && (*it)->can_move() == true)
                { // car is ready to move

                    std::vector<std::string> pathbfs = bfs(vertex_ptr->name, (*it)->destination_city);
                    if(pathbfs.empty())
                    {
                        ++it;
                        continue;
                    }
                    (*it)->next_link = pathbfs[1];

                    link_groups_bfs[(*it)->next_link].push_back(&(*(*it)));
                    it = vertex.sealed_freight_cars.erase(it); // Erase and advance the iterator
                }
                else
                {
                    ++it; // Only advance the iterator
                }
            }

            // Try forming trains with the grouped cars based on BFS
            for (auto &[link, cars] : link_groups_bfs)
            {
                if (cars.size() >= vertex.min_freight_cars_to_move)
                {
                    // Move cars to trains_to_move if there are enough to form a train
                    for (auto *car_ptr : cars)
                    {
                        vertex.trains_to_move[link].push_back(car_ptr);
                        // vertex.trains_ptr[link].push_back(car_ptr);
                        // As the car is added to a train, remove it from sealed_freight_cars
                        // auto sealed_it = std::find(vertex.sealed_freight_cars.begin(), vertex.sealed_freight_cars.end(), *car_ptr);
                        // if (sealed_it != vertex.sealed_freight_cars.end())
                        // {
                        //     vertex.sealed_freight_cars.erase(sealed_it);
                        // }
                    }
                }
                else
                {
                    // Not enough cars for a BFS train, try grouping them by DFS next link
                    for (auto *car_ptr : cars)
                    {
                        std::vector<std::string> visitt = car_ptr->visited_vertices;
                        std::string nextt;
                        // std::vector<std::string> pathdfs = find_dfs_path_no_repetition(vertex_ptr->name, car_ptr->destination_city, visitt);
                        std::vector<std::string> pathdfs = dfs(vertex_ptr->name, car_ptr->destination_city);
                        if (!pathdfs.empty())
                        {
                            std::vector<std::string> pathss = pathdfs;
                            if (!pathss.empty())
                            {
                                if (!contains_visited(pathss, visitt))
                                {
                                    nextt = pathss[1];
                                    car_ptr->next_link = nextt;

                                    link_groups_dfs[car_ptr->next_link].push_back(car_ptr);
                                }

                                else
                                {
                                    // nextt = "arandomlinkdontgroupthis......";
                                    car_ptr->next_link.clear();
                                    if (car_ptr->sealed)
                                    {
                                        vertex.sealed_freight_cars.push_back(car_ptr);
                                    }

                                    else
                                    {
                                        vertex.freight_cars.push_back(car_ptr);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            // Process the DFS groups to form trains or add to existing BFS trains
            for (auto &[link, cars] : link_groups_dfs)
            {
                if (vertex.trains_to_move.count(link) && (vertex.trains_to_move[link].size() + cars.size()) >= vertex.min_freight_cars_to_move)
                {
                    // Add to existing BFS train
                    for (auto *car_ptr : cars)
                    {
                        vertex.trains_to_move[link].push_back(car_ptr);
                        // vertex.trains_ptr[link].push_back(car_ptr);
                        // Remove car from sealed_freight_cars
                        // auto sealed_it = std::find(vertex.sealed_freight_cars.begin(), vertex.sealed_freight_cars.end(), *car_ptr);
                        // if (sealed_it != vertex.sealed_freight_cars.end())
                        // {
                        //     vertex.sealed_freight_cars.erase(sealed_it);
                        // }
                    }
                }
                else if (cars.size() >= vertex.min_freight_cars_to_move)
                {
                    // Form a new DFS train
                    for (auto *car_ptr : cars)
                    {
                        vertex.trains_to_move[link].push_back(car_ptr);
                        // vertex.trains_ptr[link].push_back(car_ptr);
                        //  Remove car from sealed_freight_cars
                        //  auto sealed_it = std::find(vertex.sealed_freight_cars.begin(), vertex.sealed_freight_cars.end(), *car_ptr);
                        //  if (sealed_it != vertex.sealed_freight_cars.end())
                        //  {
                        //      vertex.sealed_freight_cars.erase(sealed_it);
                        //  }
                    }
                }
                else
                {
                    // Add cars back to sealed_freight_cars if they cannot form a train
                    for (auto *car_ptr : cars)
                    {
                        if (car_ptr->sealed)
                        {
                            vertex.sealed_freight_cars.push_back(car_ptr);
                        }

                        else
                        {
                            vertex.freight_cars.push_back(car_ptr);
                        }
                    }
                }
            }
        }
    }

    void moveTrains()
    {
        // for every vertex, move freight cars to next link

        for (auto &vertex_ptr : vertices)
        {
            Vertex &vertex = *vertex_ptr;

            // Process each train ready to move at this vertex
            for (auto it = vertex.trains_to_move.begin(); it != vertex.trains_to_move.end();)
            {
                std::string link = it->first;
                std::vector<FreightCar *> &train = it->second;

                // Find the destination vertex for this link
                Vertex *destination_vertex = nullptr;

                for (auto ver : vertex_ptr->get_neighbors())
                {
                    if (ver->name == link)
                    {
                        destination_vertex = ver;
                    }
                }

                if (destination_vertex)
                {
                    // Move each freight car in the train to the destination's sealed_freight_cars
                    for (FreightCar *&car : train)
                    {
                        destination_vertex->sealed_freight_cars.push_back(car);
                        car->move(destination_vertex->name);
                    }
                    // Remove the train from the current vertex's trains_to_move as it has been processed
                    it = vertex.trains_to_move.erase(it);
                    // vertex.trains_to_move.erase(link);
                }
                else
                {
                    // If no destination vertex is found, the train cannot move
                    ++it;
                }
            }
        }
    }
};

class PRC
{
public:
    Graph graph;
    std::vector<FreightCar *> freight_cars;
    std::map<std::string, Parcel *> parcels;
    std::map<int, std::vector<Parcel *>> parcels_with_time_tick;
    int max_parcel_capacity;
    int min_freight_cars_to_move;
    int time_tick;
    std::map<std::string, std::string> old_state;
    std::map<std::string, std::string> new_state;
    int max_time_tick;
    std::map<std::string, Parcel *> current_parcels;

    PRC(int max_parcel_capacity, int min_freight_cars_to_move)
    {
        this->max_parcel_capacity = max_parcel_capacity;
        this->min_freight_cars_to_move = min_freight_cars_to_move;
        this->time_tick = 1;
        this->max_time_tick = 100;
        this->freight_cars = {};
        this->parcels = {};
        this->parcels_with_time_tick = {};
        this->old_state = {};
        this->new_state = {};
    }

    void create_graph(std::string graph_file_name)
    {

        // read graph.txt file and create graph

        std::ifstream graph_file(graph_file_name);
        std::string line;

        while (std::getline(graph_file, line))
        {
            std::istringstream iss(line);
            std::string city1, city2;

            // Parse the line
            std::getline(iss, city1, ' '); // Read up to the first space
            std::getline(iss, city2, ' '); // Read up to the second space

            // Add vertices and an edge between them

            graph.add_edge(city1, city2, min_freight_cars_to_move, max_parcel_capacity);
        }
    }

    void process_parcels(std::string parcels_file_name)
    {
        // read parcels.txt file and create parcels
        // read parcels.txt file and create parcels
        std::ifstream parcels_file(parcels_file_name);
        std::string line;

        while (std::getline(parcels_file, line))
        {
            std::istringstream iss(line);
            std::string time_tick_str, priority_str;
            std::string parcel_id, source, destination;

            // Parse the line
            std::getline(iss, time_tick_str, ' ');
            std::getline(iss, parcel_id, ' ');
            std::getline(iss, source, ' ');
            std::getline(iss, destination, ' ');
            std::getline(iss, priority_str, ' ');

            // Convert string to int
            int time_ticker = std::stoi(time_tick_str);
            int priority = std::stoi(priority_str);

            // Create a parcel object
            Parcel *parcel = new Parcel(time_ticker, parcel_id, source, destination, priority);
            // Insert the parcel into the booking system
            parcels[parcel_id] = parcel;
            // Use the time_tick to group parcels
            parcels_with_time_tick[time_ticker].push_back(parcel);
        }
    }

    // function to return bookings at a particular time tick at a particular vertex
    std::vector<Parcel *> get_bookings(int time_tic, std::string vertex)
    {
        std::vector<Parcel *> pss;
        for (auto i : parcels_with_time_tick[time_tic])
        {
            if (i->origin == vertex)
            {
                pss.push_back(i);
            }
        }
        return pss;
    }

    std::map<std::string, std::string> get_state()
    {
        std::map<std::string, std::string> state;
        // from this.parcels
        state = new_state;
        // should return the dict of parcel_id and current_location
        return state;
    }

    // run simulation function, takes run_till_time_tick as argument
    // if run_till_time_tick is not provided then run simulation till max_time_tick

    void run_simulation(int run_till_time_tick = -1)
    {

        // function to run simulation
        if (run_till_time_tick == -1)
        {
            run_till_time_tick = max_time_tick;
        }

        for (time_tick; time_tick < run_till_time_tick; time_tick++)
        {

            freight_cars.clear();

            for (auto &pars : parcels_with_time_tick[time_tick])
            {
                pars->updatetick(time_tick);
                current_parcels[pars->parcel_id] = pars;

                Vertex *parcel_node = graph.find_vertex(pars->current_location);

                if (parcel_node == nullptr)
                {
                    parcel_node = new Vertex(pars->origin, min_freight_cars_to_move, max_parcel_capacity);
                }

                parcel_node->loadParcel(pars);
            }

            for (auto ver : graph.vertices)
            {
                ver->loadFreightCars();
            }

            graph.groupFreightCars();

            graph.moveTrains();
            old_state = new_state;
            new_state.clear();

            for (auto ver : graph.vertices)
            {
                ver->clean_unmoved_freight_cars();

                for (auto kalll : ver->sealed_freight_cars)
                {
                    freight_cars.push_back(kalll);
                }
                for (auto kk : ver->trains_to_move)
                {
                    for (auto kl : kk.second)
                        freight_cars.push_back(kl);
                }
            }

            for (auto parr : current_parcels)
            {
                parr.second->updatetick(time_tick + 1);
                new_state[parr.first] = parr.second->current_location;
            }

            if (convergence_check())
            {
                break;
            }
        }
    }

    bool convergence_check()
    {
        if (old_state == new_state)
        {
            return true;
        }
        else
        {
            return false;
        }
        // // function to check convergence between old_state and new_state
        // if(old_state.size() == new_state.size())
        // {
        //     if()
        // }
    }

    bool all_parcels_delivered()
    {
        for (auto &parcel_pair : this->parcels)
        {
            Parcel *&parcel = parcel_pair.second;
            if (!parcel->delivered)
            {
                return false;
            }
        }
        return true;
    }

    std::vector<std::string> get_stranded_parcels()
    {
        // return parcel_ids of stranded parcels
        // return parcel_ids of stranded parcels
        std::vector<std::string> strandedparcels;

        for (auto i : current_parcels)
        {
            if (i.second->delivered == false)
            {
                strandedparcels.push_back(i.first);
            }
        }
        return strandedparcels;
    }

    std::vector<std::string> get_delivered_parcels()
    {
        // return parcel_ids of delivered parcels
        // return parcel_ids of delivered parcels
        std::vector<std::string> strandedparcels;

        for (auto i : current_parcels)
        {
            if (i.second->delivered == true)
            {
                strandedparcels.push_back(i.first);
            }
        }
        return strandedparcels;
    }

    // get status of all parcels at time tick t (status = id, current location, delivered/not delivered)
    std::vector<std::string> get_status_of_all_parcels(int t)
    {
        std::vector<std::string> all;
        for (auto paa : current_parcels)
        {
            all.push_back(get_status_of_parcel(paa.first, t));
        }
        return all;
        //  std::string status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered) + "\n" ;
        // return the status of all parcels at time tick t as a vector of strings (each string formatted as above)
    }

    // get status of parcel_id at time tick t (status = id, current location, delivered/not delivered)
    std::string get_status_of_parcel(std::string parcel_id, int t)
    {
        // status = parcel.parcel_id + " " + parcel.current_location + " " + std::to_string(parcel.delivered);
        // return status of one parcel at time tick t as a string (formatted as above)
        std::string s;
        auto it = current_parcels[parcel_id];
        if (it != nullptr)
        {
            s = parcel_id + " " + it->tick_location[t] + " " + std::to_string(it->deliveredat == t);
        }

        return s;
    }

    // get parcels delivered up to time tick t
    std::vector<std::string> get_parcels_delivered_up_to_time_tick(int t)
    {
        std::vector<std::string> delii;
        // return list of parcel_ids of parcels delivered up to time tick t
        for (auto parr : current_parcels)
        {
            if (parr.second->delivered == true && parr.second->deliveredat <= t)
            {
                delii.push_back(parr.first);
            }
        }
        return delii;
    }

    //~PRC() {
    // std::cout<<"hih";
    // std::cout<<"llsos";

    // int kaksk = 0;

    //     // Delete all dynamically allocated FreightCars
    //    for (auto &vertex_ptr : graph.vertices) {

    //        delete vertex_ptr;
    //        vertex_ptr = nullptr;
    //    }

    //         // Delete freight cars not in trains
    //         for (FreightCar* car : vertex.freight_cars) {
    //             delete car;  // Assuming FreightCar was allocated with new
    //         }

    //         // Delete sealed freight cars
    //         for (FreightCar* car : vertex.sealed_freight_cars) {
    //             delete car;  // Assuming FreightCar was allocated with new
    //         }

    //         // Delete trains
    //         for (auto &train : vertex.trains_to_move) {
    //             for (FreightCar* car : train.second) {
    //                 delete car;  // Assuming FreightCar was allocated with new
    //             }
    //         }

    //         // Delete any other dynamically allocated FreightCars that PRC may be managing
    //         // ...

    //         // Delete Parcels
    //         for (Parcel* parcel : vertex.all_parcels) {
    //             delete parcel;  // Assuming Parcel was allocated with new
    //         }
    //         delete vertex_ptr;
    //     }

    //     // for(auto & ptr : freight_cars)
    //     // {
    //     //     delete ptr;
    //     // }

    //     // for(auto ptr : freight_cars)
    //     // {
    //     //     delete ptr;
    //     // }

    //     // for(auto & ptr : parcels)
    //     // {
    //     //     delete ptr;
    //     // }
    // }
};

// int main() {

//     PRC prc = PRC(2, 2);
//     prc.create_graph();
//     prc.process_parcels();
//     prc.run_simulation(3);

//     return 0;
// }

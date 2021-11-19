#include <iostream>
#include <stdio.h>
#include <string.h>
#include "linkedList.h"

using namespace std;

void wagonNode::set_next(wagonNode *next)
{
    this->next = next;
}
wagonNode *wagonNode::get_next()
{
    return this->next;
}

void materialNode::set_next_mat(materialNode *next)
{
    this->next = next;
}
materialNode *materialNode::get_next_mat()
{
    return this->next;
}

void Train::create()
{
    head = NULL;
};

materialNode *material_head;
materialNode *y;
materialNode *x;
wagonNode *p;
wagonNode *global_head;
int wagonId = 1;
int Vagonnumber()
{ /* Finds number of vagons*/
    int i = 0;
    wagonNode *tempWagon = global_head;
    while (tempWagon != NULL)
    {
        i += 1;
        tempWagon = tempWagon->next;
    }
    return i;
}
int Materialnumber(wagonNode *vagon_point)
{ /* Finds number of materials inside a vagon */
    int i = 0;
    wagonNode *tempWagon = vagon_point;

    materialNode *temp_mat = tempWagon->material;
    while (temp_mat != NULL)
    {
        i += 1;

        temp_mat = temp_mat->next;
    }

    return i;
}
wagonNode *prevWagonAdress(int vagon, wagonNode *vagon_point)
{ /* Finds the prev wagon address */
    wagonNode *tempWagon = global_head;

    if (vagon >= 3)
    {
        while (tempWagon->next != vagon_point)
        {
            tempWagon = tempWagon->next;
        }
        return tempWagon;
    }
    if (vagon <= 2)
    {
        return tempWagon;
    }
    return tempWagon;
}
materialNode *prevMatAdress(materialNode *adress)
{ /* Finds the prev mat adress of given mat */
    wagonNode *temp_wagon = global_head;
    while (temp_wagon != NULL)
    {

        materialNode *temp_mat = temp_wagon->material;
        while (temp_mat != NULL)
        {
            if (temp_mat->next == adress)
            {
                return temp_mat;
            }

            temp_mat = temp_mat->next;
        }
        temp_wagon = temp_wagon->next;
    }
    return NULL;
}
wagonNode *LastWagonAdress(int vagon)
{ /* Finds the wagon that is last */
    wagonNode *tempWagon = global_head;

    if (vagon == 1)
    {
        return tempWagon;
    }
    if (vagon >= 2)
    {
        while (tempWagon->next != NULL)
        {
            tempWagon = tempWagon->next;
        }
    }
    return tempWagon;
}

materialNode *GetTailMat(wagonNode *vagon_point)
{ /* Gets the tail mat of a wagon */
    wagonNode *tempWagon = vagon_point;
    materialNode *TempMaterial = tempWagon->material;

    while (TempMaterial->next != NULL)
    {
        TempMaterial = TempMaterial->next;
    }
    return TempMaterial;
}

wagonNode *WagonSearcher(wagonNode *vagon_point, char c, int weight, int vagon_num)
{ /* The most important func of my code , looks for a material_id in a vagon*/

    wagonNode *functionwagon = vagon_point;

    int vagon = 0;
    while (functionwagon != NULL)
    {

        int key = 0;
        materialNode *functionMat = functionwagon->material;
        while (functionMat != NULL)
        {
            if (functionMat->id == c && (functionMat->weight) + weight >= 2000)
            {

                vagon += 1;
            }
            if (functionMat->id == c)
            {

                key += 1;
            }

            functionMat = functionMat->next;
        }

        if (key == 0)
        {

            return functionwagon;
        }
        functionwagon = functionwagon->next;
    }
    if (vagon == vagon_num)
    {
        return NULL;
    }
    return NULL;
}
wagonNode *EmptyWagonFinder(wagonNode *vagon_point, char c, int weight)
{ /* Returns the first <2000 material value */
    wagonNode *functionwagon = vagon_point;

    while (functionwagon != NULL)
    {

        materialNode *functionMat = functionwagon->material;
        while (functionMat != NULL)
        {

            if (functionMat->id == c && (functionMat->weight) < 2000)
            {

                return functionwagon;
            }

            functionMat = functionMat->next;
        }
        functionwagon = functionwagon->next;
    }
    return vagon_point;
}
int ThousandFinder(int weigt)
{ /* Gets the mod if number is bigger than 2000 */
    int times = 0;
    int mod = 0;
    int temp_weigt = weigt;
    while (true)
    {
        mod = temp_weigt % 2000;
        times++;
        if (mod < 2000)
        {
            break;
        }
    }
    return mod;
}
int TimesFinder(int weigt)
{ /* Finds how many 2000s inside weight */
    int times = 0;
    int temp_weight = weigt;
    while (temp_weight >= 2000)
    {
        temp_weight -= 2000;
        times += 1;
    }
    return times;
}
int TotalWeightFromWagons(char c){ /* Finds the total weight of a material on all wagons */
    wagonNode *functionwagon = global_head;
    int total=0;

    while (functionwagon != NULL)
    {

        materialNode *functionMat = functionwagon->material;
        while (functionMat != NULL)
        {
            if(functionMat->id==c){
                total+=functionMat->weight;
            }

            functionMat = functionMat->next;
        }
        functionwagon = functionwagon->next;
    }
    return total;

}

int Reorder(wagonNode *vagon_point)
{ /* Reorders all vagons by alphabetical order*/

    wagonNode *temp_wagon = vagon_point;
    while (temp_wagon != NULL)
    {

        materialNode *temp_mat = temp_wagon->material;
        while (temp_mat != NULL)
        {
            if (temp_mat != temp_wagon->material)
            {
                if (temp_mat->next != NULL)
                {
                    if (temp_mat->id > temp_mat->next->id)
                    {
                        materialNode *keeper;
                        materialNode *keeper2;
                        materialNode *prev_wagon = prevMatAdress(temp_mat);
                        keeper2 = temp_mat->next->next;
                        keeper = temp_mat;
                        prev_wagon->next = temp_mat->next;
                        temp_mat->next->next = keeper;
                        temp_mat->next = keeper2;
                    }
                }
            }
            else
            {
                if (temp_mat->next != NULL)
                {

                    if (temp_mat->id > temp_mat->next->id)
                    {
                        materialNode *keeper;
                        materialNode *keeper2;
                        keeper2 = temp_wagon->material->next->next;
                        keeper = temp_wagon->material;
                        temp_wagon->material = temp_wagon->material->next;
                        temp_wagon->material->next = keeper;
                        temp_wagon->material->next->next = keeper2;
                    }
                }
            }
            temp_mat = temp_mat->next;
        }
        temp_wagon = temp_wagon->next;
    }
    wagonNode *temp_wagon2 = vagon_point;
    int fully_reordered = 0;
    while (temp_wagon2 != NULL)
    {

        materialNode *temp_mat2 = temp_wagon2->material;
        while (temp_mat2->next != NULL)
        {
            if (temp_mat2->id < temp_mat2->next->id)
            {
                fully_reordered += 1;
            }
            temp_mat2 = temp_mat2->next;
        }
        if (fully_reordered == Materialnumber(temp_wagon2) - 1)
        { /* Checks if wagons are fully reordered */
            return 1;
        }

        temp_wagon2 = temp_wagon2->next;
    }
    return 0;
}

void Train::addMaterial(char material, int weight)
{
    //FILL THIS FUNCTION ACCORDINGLY

    int check3 = 1;
    int check4 = 1;

    if (head == NULL)
    { /*First wagon assignment */
        int temp = ThousandFinder(weight);
        int i = TimesFinder(weight);

        if (i == 0)
        {
            head = new wagonNode();
            p = head;
            global_head = head;
            p->wagonId = wagonId;
            wagonId += 1;
            p->material = new materialNode();
            material_head = p->material;
            y = p->material;
            y->id = material;
            y->weight = weight;
        }
        else
        {
            if (temp != 0)
            {
                i = i + 1;
            }
            int a = i;
            while (i != 0)
            {
                if (i == a)
                {
                    head = new wagonNode();
                    p = head;
                    global_head = head;
                    p->wagonId = wagonId;
                    wagonId=Vagonnumber()+1;
                }
                else
                {
                    p->set_next(new wagonNode());
                    p = p->get_next();
                    p->wagonId = wagonId;
                    wagonId=Vagonnumber()+1;
                }
                if (i != 1)
                {
                    p->material = new materialNode();
                    p->material->weight = 2000;
                    p->material->id = material;
                }
                i--;
            }
            if (LastWagonAdress(Vagonnumber())->material == NULL)
            { /* If the last wagon material is null create a new mat_node */

                wagonNode *tempwagon5 = LastWagonAdress(Vagonnumber());

                tempwagon5->material = new materialNode();
                x = tempwagon5->material;
                if (temp != 0)
                {
                    x->weight = temp;
                }
                else
                {
                    x->weight = 2000;
                }

                x->id = material;
            }
        }
    }

    else
    {

        wagonNode *tempWagon = EmptyWagonFinder(head, material, weight); /* Finds the first <2000 value for given material in wagons */

        materialNode *tempMat = tempWagon->material;

        while (tempMat != NULL)
        {

            if (tempMat->id == material && (tempMat->weight) + weight > 2000)
            {

                int temp = ThousandFinder(weight + tempMat->weight);

                if (WagonSearcher(head, material, weight, Vagonnumber()) == NULL)
                {

                    int i = TimesFinder(weight + tempMat->weight);
                    if (temp == 0)
                    {
                        i--;
                    }
                    while (i != 0)
                    {

                        p->set_next(new wagonNode());
                        p = p->get_next();
                        p->wagonId = wagonId;
                        wagonId=Vagonnumber()+1;
                        check3 = 0;
                        if (i != 1)
                        {
                            p->material = new materialNode();
                            p->material->weight = 2000;
                            p->material->id = material;
                        }
                        i--;
                    }
                }

                if (LastWagonAdress(Vagonnumber())->material == NULL)
                {

                    wagonNode *tempwagon5 = LastWagonAdress(Vagonnumber());

                    tempwagon5->material = new materialNode();
                    x = tempwagon5->material;
                    if (temp != 0)
                    {
                        x->weight = temp;
                    }
                    else
                    {
                        x->weight = 2000;
                    }

                    tempMat->weight = 2000;
                    x->id = material;
                    check4 = 0;
                }

                if (check4)
                {

                    int thousand = ThousandFinder(weight + tempMat->weight);
                    int times = TimesFinder(weight + tempMat->weight);

                    while (times != 0)
                    {
                        wagonNode *temp = WagonSearcher(head, material, weight, Vagonnumber());

                        if (WagonSearcher(head, material, weight, Vagonnumber()) != NULL)
                        {

                            materialNode *temp2 = GetTailMat(temp);
                            temp2->set_next_mat(new materialNode());
                            temp2 = temp2->get_next_mat();
                            if (times != 1)
                            {
                                temp2->weight = 2000;
                                temp2->id = material;
                            }
                            else
                            {
                                temp2->weight = thousand;
                                temp2->id = material;
                                tempMat->weight = 2000;
                            }
                        }
                        else
                        {
                            if (thousand != 0)
                            {

                                wagonNode *lastwagon = LastWagonAdress(Vagonnumber());
                                lastwagon->set_next(new wagonNode());
                                lastwagon = lastwagon->get_next();
                                lastwagon->wagonId = wagonId;
                                materialNode *temp3;
                                wagonId=Vagonnumber()+1;
                                if (times != 1)
                                {
                                    lastwagon->material = new materialNode();
                                    temp3 = lastwagon->material;

                                    temp3->weight = 2000;
                                    temp3->id = material;
                                }
                            }
                            else
                            {
                                if (times == 1)
                                {
                                    wagonNode *lastwagon = LastWagonAdress(Vagonnumber());
                                    lastwagon->set_next(new wagonNode());
                                    lastwagon = lastwagon->get_next();
                                    lastwagon->wagonId = wagonId;
                                    wagonId=Vagonnumber()+1;
                                    lastwagon->material = new materialNode();
                                    materialNode *temp3 = lastwagon->material;

                                    temp3->weight = 2000;
                                    temp3->id = material;
                                }

                                tempMat->weight = 2000;
                            }
                        }
                        if (LastWagonAdress(Vagonnumber())->material == NULL)
                        {

                            wagonNode *tempwagon5 = LastWagonAdress(Vagonnumber());

                            tempwagon5->material = new materialNode();
                            x = tempwagon5->material;

                            if (thousand != 0)
                            {
                                x->weight = thousand;
                            }
                            else
                            {
                                x->weight = 2000;
                            }
                            tempMat->weight = 2000;
                            x->id = material;
                        }

                        times--;
                    }
                    check3 = 0;
                }
            }

            tempMat = tempMat->next;
        }

        if (check3)
        {

            tempWagon = EmptyWagonFinder(head, material, weight);
            int check2 = 1;
            tempMat = tempWagon->material;

            while (tempMat != NULL)
            {

                if (tempMat->id == material && (tempMat->weight) + weight <= 2000)
                {

                    tempMat->weight += weight;
                    check2 = 0;
                    break;
                }

                tempMat = tempMat->next;
            }

            if (check2)
            {

                if (weight > 2000)
                {

                    int thousand = ThousandFinder(weight);
                    int times = TimesFinder(weight);
                    if (thousand != 0)
                    {
                        times += 1;
                    }

                    while (times != 0)
                    {
                        wagonNode *temp = WagonSearcher(head, material, weight, Vagonnumber());

                        if (WagonSearcher(head, material, weight, Vagonnumber()) != NULL)
                        { /* Searching for a wagon that has no material for given char */
                            materialNode *temp2 = GetTailMat(temp);
                            temp2->set_next_mat(new materialNode());
                            temp2 = temp2->get_next_mat();
                            if (times != 1)
                            {

                                temp2->weight = 2000;
                                temp2->id = material;
                            }
                            else
                            {
                                if (thousand != 0)
                                {
                                    temp2->weight = thousand;
                                }
                                else
                                {
                                    temp2->weight = 2000;
                                }

                                temp2->id = material;
                            }
                        }

                        else
                        {

                            wagonNode *lastwagon = LastWagonAdress(Vagonnumber());

                            lastwagon->set_next(new wagonNode());
                            lastwagon = lastwagon->get_next();
                            lastwagon->wagonId = wagonId;

                            wagonId=Vagonnumber()+1;
                            if (times != 1)
                            {
                                lastwagon->material = new materialNode();
                                materialNode *temp3 = lastwagon->material;

                                temp3->weight = 2000;
                                temp3->id = material;
                            }
                        }

                        times--;
                    }
                }
                else
                {
                    wagonNode *temp = WagonSearcher(head, material, weight, Vagonnumber());
                    materialNode *temp2 = GetTailMat(temp);

                    temp2->set_next_mat(new materialNode());
                    temp2 = temp2->get_next_mat();
                    temp2->weight = weight;

                    temp2->id = material;
                }
                if (LastWagonAdress(Vagonnumber())->material == NULL)
                {

                    wagonNode *tempwagon5 = LastWagonAdress(Vagonnumber());
                    int thousand = ThousandFinder(weight);
                    tempwagon5->material = new materialNode();
                    x = tempwagon5->material;

                    if (thousand != 0)
                    {

                        x->weight = thousand;
                    }
                    else
                    {
                        x->weight = 2000;
                    }
                    x->id = material;
                }
            }
        }
    }

    if (Vagonnumber() != 1 || head->material->next != NULL)
    { /* Reordering happens here */
        int vagon_counter = 0;
        wagonNode *temp_wagon_name = head;
        while (Vagonnumber() != vagon_counter)
        {
            if (Reorder(temp_wagon_name) == 1)
            {

                temp_wagon_name = temp_wagon_name->next;
                vagon_counter += 1;
            }
        }
    }
};

void Train::deleteFromWagon(char material, int weight)
{

    wagonNode *temp_wagon = LastWagonAdress(Vagonnumber());
    int temp_weight = weight;
    int weight_holder=TotalWeightFromWagons(material);
    while (temp_wagon != NULL)
    {

        if (temp_weight != 0)
        { /* Firstly make wagons 0 kg*/
            materialNode *temp_mat = temp_wagon->material;

            while (temp_mat != NULL)
            {
                if (temp_mat->id == material)
                {
                    if (temp_mat->weight > temp_weight)
                    {

                        temp_mat->weight = (temp_mat->weight) - temp_weight;
                        temp_weight = 0;
                        wagonId -= 1;
                    }
                    else
                    {
                        temp_weight = temp_weight - temp_mat->weight;
                        temp_mat->weight = 0;
                        wagonId -= 1;
                    }
                }
                temp_mat = temp_mat->next;
            }
        }
        else
        {
            break;
        }
        if (temp_wagon->wagonId != 1)
        {
            temp_wagon = prevWagonAdress(Vagonnumber(), temp_wagon); /* Starting from last to first */
        }
        else
        {
            break;
        }
    }

    temp_wagon = global_head;
   
    while (temp_wagon != NULL)
    { /*Secondly delete all 0 kg materials */

        materialNode *temp_mat = temp_wagon->material;
        while (temp_mat != NULL)
        {
            if (temp_mat->weight == 0 && temp_mat->id == material)
            {
                if (Materialnumber(temp_wagon) == 1)
                {
                    if(weight_holder==weight){
                        temp_wagon->next=NULL;
                    }
                        
                    else{
                        prevWagonAdress(Vagonnumber(),temp_wagon)->next=temp_wagon->next;
                        
                    }
                    
                    break;
                    
                }
                else
                {
                    if (temp_wagon->material == temp_mat)
                    {

                        temp_wagon->material = temp_wagon->material->next;
                    }
                    else
                    {

                        materialNode *prev_wagon = prevMatAdress(temp_mat);

                        prev_wagon->next = temp_mat->next;
                    }
                }
            }
            temp_mat = temp_mat->next;
        }

        temp_wagon = temp_wagon->next;
    }

    if (Vagonnumber() == 1 && Materialnumber(head) == 1 && head->material->weight == 0)
    { /* If all wagons are empty */
        head = NULL;
    }
};

void Train::printWagon()
{
    wagonNode *tempWagon = head;

    if (tempWagon == NULL)
    {
        cout << "Train is empty!!!" << endl;
        return;
    }

    while (tempWagon != NULL)
    {
        materialNode *tempMat = tempWagon->material;
        cout << tempWagon->wagonId << ". Wagon:" << endl;
        while (tempMat != NULL)
        {
            cout << tempMat->id << ": " << tempMat->weight << "KG, ";
            tempMat = tempMat->next;
        }
        cout << endl;
        tempWagon = tempWagon->next;
    }
    cout << endl;
};



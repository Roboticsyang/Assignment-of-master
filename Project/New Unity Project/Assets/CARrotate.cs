using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CARrotate : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        //按A键向左转头
        if (Input.GetKey(KeyCode.Q))
        {
            // transform.position += -transform.right * speed * Time.deltaTime;
            transform.Rotate(-Vector3.up * 50 * Time.deltaTime);
        }
        //按D键向右转头
        if (Input.GetKey(KeyCode.E))
        {
            // transform.position += transform.right * speed * Time.deltaTime;
            transform.Rotate(Vector3.up * 50 * Time.deltaTime);
        }
    }
}

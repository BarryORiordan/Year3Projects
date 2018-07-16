/*
   Author: Barry O' Riordan - 13144278
   Description: CS4006 Final Submission
*/

import java.io.File;
import java.util.Scanner;
import java.awt.Graphics;
import javax.swing.JFrame;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.io.IOException;
import java.util.Collections;

public class is13144278 extends JFrame
{
	static int c = 0;
	static int adj[][];  //Adjacency Matrix
	static int r = 0;   //Number of Nodes
	static int nodes = 0;
	static int adjL[][];
	static int incM[][];
	static int current_ordering[];
	static double cooling_rate = .0005;
	static double current_fitness = 0;
	static double chunk;
	static ArrayList<String> ordering = new ArrayList<String>();

	//Constructor to visualize the output
	public is13144278()
	{
		setTitle("is13144278 - CS4006 Final Submission Output");
		setSize(400, 400);
		setVisible(true);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
	}

	public void paint(Graphics g)
	{
		int mov    = 200;
		int radius = 100;

		for(int i = 0; i < r; i++)
			for(int j = i + 1; j < r; j++)
				if(adj[current_ordering[i]][current_ordering[j]] == 1)
					g.drawLine(
							  (int) (((double) Math.cos(i * chunk)) * radius + mov),
							  (int) (((double) Math.sin(i * chunk)) * radius + mov),
							  (int) (((double) Math.cos(j * chunk)) * radius + mov),
							  (int) (((double) Math.sin(j * chunk)) * radius + mov));
	}
	
	public static void main (String [] args) throws IOException
	{		
		create();
		print();

		//current_ordering of nodes is filled with the randomly generated order.
		current_ordering = new int[r];
		for(int i = 0; i < r; i++)
			current_ordering[i] = Integer.parseInt(ordering.get(i));
		
		current_fitness = fitness(current_ordering);
		temp();
		is13144278 visualization = new is13144278();
	}
	
	static void create() throws IOException
	{
		//Find out size of 2D array needed
		Scanner in  = new Scanner(new File("input.txt"));
		Scanner in2;
		
		//Constantly read row until there is no more, each nextLine = a row
		while(in.hasNextLine())
		{
			in2 = new Scanner(in.nextLine());
			while(in2.hasNextInt())
			{
				int temp = in2.nextInt();
				nodes++;
			}
			r++;
		}
		//chunk can now be set since we know the amount of rows
		chunk = ((2 * Math.PI) / r);
		
		//we can now also get columns within the file by / the amount of 0 and 1's by the rows
		in = new Scanner(new File("input.txt"));
		c = (int) (nodes / r);
		//incidence matrix can be created now since we know dimensions
		incM = new int[r][c];
		
		//read through file again to populate the matrix
		for(int a = 0; a < r; a++)
			for(int b = 0; b < c; b++)
				if(in.hasNextInt())
					incM[a][b] = in.nextInt();
		
		in.close();
		
		//create the adj list from the inc matrix input
		adjL = new int[c][3];
		for(int a = 0; a < c; a++)
			adjL[a][0] = (a + 1);
		
		for(int a = 0; a < r; a++)
			for(int b = 0; b < c; b++)
				if(incM[a][b] == 1)
				{
					if(adjL[b][1] == 0)	   adjL[b][1] = (a + 1);
					else			       adjL[b][2] = (a + 1);
				}
	}

	static void print() throws IOException
	{
		//square 2d adj matrix created from adj list
		//match the nodes in list to matching ones in the matrix
		adj = new int[r][r];
		int n1;
		int n2;
		String order;
		for(int a = 0; a < c; a++)
		{
			n1 = adjL[a][1];
			n2 = adjL[a][2];
			
			adj[n1 - 1][n2 - 1] = 1;
			adj[n2 - 1][n1 - 1] = 1;
		}

		//loop though the aj matcric and print each element to AI16
		PrintWriter print = new PrintWriter("AI16.txt");
		int element;

		for(int a = 0; a < r; a++)
		{
			for(int b = 0; b < r; b++)
			{
				element = adj[a][b];
				print.write(element + " ");
			}
			print.write("\n");
		}
		print.write("\n");
		
		//the number of rows of adjM are added to the arraylist
		for(int a = 0; a < r; a++)
			ordering.add(Integer.toString(a));
		
		order = "{";
		//shuffle is used to randomly generated an ordering of the numbers
		Collections.shuffle(ordering);
		for(int i = 0; i < r; i++)
		{
			if(i == (r - 1))	order += ordering.get(i) + "}";
			else				order += ordering.get(i) + ",";
		}
		print.write(order);
		print.close();
	}
	
	//get fitness of ordering
	static double fitness(int ordering_copy[])
	{
		double xdoti, xdotj, ydoti, ydotj;
		double d = 0;
		
		for(int i = 0; i < r; i++)
			for(int j = i + 1; j < r; j++)
				if(adj[ordering_copy[i]][ordering_copy[j]] == 1)
				{
					xdoti = Math.cos(i * chunk);
					ydoti = Math.sin(i * chunk);
					xdotj = Math.cos(j * chunk);
					ydotj = Math.sin(j * chunk);
					
					d += ((xdotj - xdoti) * (xdotj - xdoti)) + 
					     ((ydotj - ydoti) * (ydotj - ydoti));
				}
		return d;
	}
	
	static void temp()
	{
		//get a set temp, from notes
		double t = r / 10;
		double temporary_fitness;
		int ordering_copy2[] = new int[r];
		//temp above 0 = system not cool
		while(t >= 0)
		{	
			//mutate ordering depding on set temp
			ordering_copy2 = current_ordering.clone();
			for(int i = 0; i < t; i++)
				ordering_copy2 = mutation(ordering_copy2);
			
			temporary_fitness = fitness(ordering_copy2);
			//if better fitness in temp due to mutation, 
			//we set current to temp so we constantly loop 
			//to get a better and better fitness
			if(temporary_fitness < current_fitness)
			{
				current_fitness = temporary_fitness;
				current_ordering = ordering_copy2.clone();
			}
			//temp is lowered
			t = t - cooling_rate;
		}
	}
	
	//mutatations are done based on the set temp
	static int[] mutation(int ordering_copy3[])
	{
		//generate two nodes
		int x1 = (int)(Math.random() * r);
		int x2 = (int)(Math.random() * r);
		//if both the same re-roll cause mutation wont work correctly
		while(x1 == x2)
		{
			x2 = (int)(Math.random() * r);
		}
		//swap generated nodes
		int y1 = ordering_copy3[x1];
		int y2 = ordering_copy3[x2];
		ordering_copy3[x1] = y2;
		ordering_copy3[x2] = y1;
		
		return ordering_copy3;
	}
}